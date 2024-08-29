#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  int sign = 0;
  if (src < 0) {
    sign = 1;
    src = -src;
  }
  set_bit(dst, sign, 127);
  dst->bits[0] = src;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL || correct_dec(src)) return 1;
  int flag = 0;
  int sign = 0;
  s21_decimal result = {0};
  s21_truncate(src, &result);
  sign = get_bit(src, 127);
  if (result.bits[1] == 0 && result.bits[2] == 0 && get_bit(result, 31) == 0) {
    *dst = (1 - 2 * sign) * (int)result.bits[0];
  } else
    flag = 1;
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  int flag = 0;
  s21_decimal value = {0};
  s21_decimal fractional_part_dec = {0};
  float val = src;
  int bit = 0;
  int k = 0;
  uint32_t f;
  int exp_f = 0;
  int fractional_part = 0;
  int sign = 0;
  memcpy(&f, &val, sizeof(f));
  for (int i = 31; i >= 0; i--) {
    bit = (f & (1 << i)) >> i;
    if (i == 31 && bit == 1) {
      sign = 1;
      val = -val;
    }
  }
  if (val < 1E-28 && val != 0.0) {
    flag = 1;
  }
  int j = 0;
  for (int i = 23; i <= 30; i++, j++) {
    bit = (f & (1 << i)) >> i;
    exp_f = exp_f + bit * pow(2, j);
  }
  exp_f = exp_f - 127;
  j = 0;
  float float_number = 0;
  if (exp_f < 0) {
    float_number = 1.0 / pow(2, -exp_f);
  } else if (exp_f < 96) {
    set_bit(&value, 1, exp_f);
  } else
    flag = 1;
  if (flag == 0) {
    exp_f--;
    for (int i = 22; i >= 0; i--, exp_f--) {
      bit = (f & (1 << i)) >> i;
      if (bit == 1) {
        if (exp_f >= 0) {
          set_bit(&value, 1, exp_f);
        } else {
          float_number = float_number + 1.0 / pow(2, -exp_f);
        }
      }
    }
    while ((float_number - (int)float_number) > 1e-9 && k < 7) {
      float_number = float_number * 10;
      k++;
    }
    fractional_part = float_number;
    if (k == 7) {
      if (fractional_part % 10 >= 5)
        fractional_part = fractional_part / 10 + 1;
      else
        fractional_part = fractional_part / 10;
      k--;
    }
    s21_from_int_to_decimal(fractional_part, &fractional_part_dec);
    for (int i = k; i > 0; i--) {
      s21_mul_by_10(value, &value);
    }
    s21_add(value, fractional_part_dec, &value);
    int k1 = 0;
    int k2 = 0;
    s21_big_decimal big_temp = {0};
    s21_decimal temp = {0};
    s21_big_decimal excess = {0};
    s21_decimal dec_with_value_1 = {0};
    dec_with_value_1.bits[0] = 1;
    for (int i = 0; i < 3; i++) {
      big_temp.bits[i] = value.bits[i];
    }
    while (!(big_temp.bits[0] == 0 && big_temp.bits[1] == 0 &&
             big_temp.bits[2] == 0)) {
      s21_big_div_by_10(big_temp, &big_temp, &excess);
      k1++;
    }
    if (k1 > 7) {
      k2 = k1 - 7;
      for (int i = 0; i < 3; i++) {
        big_temp.bits[i] = value.bits[i];
      }
      for (int i = 0; i < k2; i++) {
        s21_big_div_by_10(big_temp, &big_temp, &excess);
      }
      for (int i = 0; i < 3; i++) {
        temp.bits[i] = big_temp.bits[i];
      }
      if (excess.bits[0] >= 5) s21_add(temp, dec_with_value_1, &temp);
      temp.bits[3] = value.bits[3];
    } else
      for (int i = 0; i < 4; i++) {
        temp.bits[i] = value.bits[i];
      }
    for (int i = 0; i < k2; i++) {
      s21_mul_by_10(temp, &temp);
    }
    for (int i = 0; i < 3; i++) {
      dst->bits[i] = temp.bits[i];
    }
    set_scale(dst, k);
    set_bit(dst, sign, 127);
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL || correct_dec(src)) {
    return 1;
  }
  int scale = 0;
  int sign = 0;
  double decimal_to_double = 0;
  scale = get_scale(src);
  sign = get_bit(src, 127);
  for (int i = 0; i < 96; i++) {
    decimal_to_double = decimal_to_double + get_bit(src, i) * pow(2, i);
  }
  for (int i = 0; i < scale; i++) {
    decimal_to_double = decimal_to_double / 10.0;
  }
  *dst = (1 - 2 * sign) * (float)decimal_to_double;
  return 0;
}