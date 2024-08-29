#include "s21_decimal.h"

// void print_decimal(s21_decimal value) {
//   for (int i = 32 * 4 - 1; i >= 0; i--) {
//     printf("%d", get_bit(value, i));
//     if (i % 32 == 0) printf(" ");
//   }
//   printf("\n");
// }

int get_bit(s21_decimal value, int index) {
  int number_int = 0;
  int number_bit = 0;
  int bit = 0;
  number_int = index / 32;
  number_bit = index % 32;

  bit = (value.bits[number_int] & (1 << number_bit)) >> number_bit;
  return bit;
}

int big_get_bit(s21_big_decimal big_value, int index) {
  int number_int = 0;
  int number_bit = 0;
  int bit = 0;
  number_int = index / 32;
  number_bit = index % 32;

  bit = (big_value.bits[number_int] & (1 << number_bit)) >> number_bit;
  return bit;
}

void set_bit(s21_decimal *value, int bit, int index) {
  int number_int = 0;
  int number_bit = 0;
  number_int = index / 32;
  number_bit = index % 32;
  if (bit == 1) {
    value->bits[number_int] = value->bits[number_int] | (1 << number_bit);
  } else
    value->bits[number_int] = value->bits[number_int] & (~(1 << number_bit));
}

void big_set_bit(s21_big_decimal *big_value, int bit, int index) {
  int number_int = 0;
  int number_bit = 0;
  number_int = index / 32;
  number_bit = index % 32;
  if (bit == 1) {
    big_value->bits[number_int] =
        big_value->bits[number_int] | (1 << number_bit);
  } else
    big_value->bits[number_int] =
        big_value->bits[number_int] & (~(1 << number_bit));
}

int get_scale(s21_decimal value) {
  int scale = 0;
  for (int i = 119; i > 111; i--) {
    int bit = get_bit(value, i);
    scale = scale * 2 + bit;
  }
  return scale;
}

int big_get_scale(s21_big_decimal value) {
  int scale = 0;
  for (int i = 215; i > 207; i--) {
    int bit = big_get_bit(value, i);
    scale = scale * 2 + bit;
  }
  return scale;
}

void set_scale(s21_decimal *value, int scale) {
  int exp = scale;
  for (int i = 0; i < 8; i++) {
    int bit = exp % 2;
    exp = exp / 2;
    set_bit(value, bit, i + 112);
  }
}

void big_set_scale(s21_big_decimal *value, int scale) {
  int exp = scale;
  for (int i = 0; i < 8; i++) {
    int bit = exp % 2;
    exp = exp / 2;
    big_set_bit(value, bit, i + 208);
  }
}

void conversion_dec_to_big_dec(s21_decimal value, s21_big_decimal *big_value) {
  for (int i = 0; i <= 2; i++) {
    big_value->bits[i] = value.bits[i];
  }
  big_value->bits[6] = value.bits[3];
}

// void print_big_decimal(s21_big_decimal big_value) {
//   for (int i = 223; i >= 0; i--) {
//     printf("%d", big_get_bit(big_value, i));
//     if (i % 32 == 0) printf(" ");
//   }
//   printf("\n");
// }

void s21_mul_by_10(s21_decimal value, s21_decimal *result) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  int mat_sum_bit = 0;
  int bit_temp = 0;
  int bit_result = 0;
  s21_decimal temp_1 = {0};
  s21_decimal temp_2 = {0};
  for (int i = 0; i < 3; i++) {
    temp_1.bits[i] = value.bits[i];
    temp_2.bits[i] = value.bits[i];
  }
  shift_left(&temp_1, 3);
  shift_left(&temp_2, 1);
  for (int i = 0; i < 32 * 3; i++) {
    bit_value_1 = get_bit(temp_1, i);
    bit_value_2 = get_bit(temp_2, i);
    mat_sum_bit = bit_value_1 + bit_value_2 + bit_temp;
    bit_temp = 0;
    bit_result = mat_sum_bit % 2;
    set_bit(result, bit_result, i);
    if (bit_result == 0 && (bit_value_1 == 1 || bit_value_2 == 1)) {
      bit_temp = 1;
    }
    if (bit_result == 1 && bit_value_1 == 1 && bit_value_2 == 1) {
      bit_temp = 1;
    }
  }
}

void s21_big_mul_by_10(s21_big_decimal big_value, s21_big_decimal *big_result) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  int mat_sum_bit = 0;
  int bit_temp = 0;
  int bit_result = 0;
  s21_big_decimal temp_1 = {0};
  s21_big_decimal temp_2 = {0};
  for (int i = 0; i < 6; i++) {
    temp_1.bits[i] = big_value.bits[i];
    temp_2.bits[i] = big_value.bits[i];
  }
  big_shift_left(&temp_1, 3);
  big_shift_left(&temp_2, 1);
  for (int i = 0; i < 32 * 6; i++) {
    bit_value_1 = big_get_bit(temp_1, i);
    bit_value_2 = big_get_bit(temp_2, i);
    mat_sum_bit = bit_value_1 + bit_value_2 + bit_temp;
    bit_temp = 0;
    bit_result = mat_sum_bit % 2;
    big_set_bit(big_result, bit_result, i);
    if (bit_result == 0 && (bit_value_1 == 1 || bit_value_2 == 1)) {
      bit_temp = 1;
    }
    if (bit_result == 1 && bit_value_1 == 1 && bit_value_2 == 1) {
      bit_temp = 1;
    }
  }
}

void shift_left(s21_decimal *value, int number_shift_left) {
  int bit = 0;
  int shift = 0;
  s21_decimal temp_1 = {0};
  for (int i = 0; i < 32 * 3; i++) {
    bit = get_bit(*value, i);
    if (0 <= 95 - shift)
      shift = i + number_shift_left;
    else
      break;
    set_bit(&temp_1, bit, i + number_shift_left);
  }
  for (int i = 0; i < 3; i++) {
    value->bits[i] = temp_1.bits[i];
  }
}

void big_shift_left(s21_big_decimal *big_value, int number_shift_left) {
  int bit = 0;
  int shift = 0;
  s21_big_decimal temp_1 = {0};
  for (int i = 0; i < 32 * 6; i++) {
    bit = big_get_bit(*big_value, i);
    if (0 <= 191 - shift)
      shift = i + number_shift_left;
    else
      break;
    big_set_bit(&temp_1, bit, shift);
  }
  for (int i = 0; i < 6; i++) {
    big_value->bits[i] = temp_1.bits[i];
  }
}

void normalization_decimals(s21_big_decimal *big_value_1,
                            s21_big_decimal *big_value_2) {
  int scale_1 = 0;
  int scale_2 = 0;
  int number_dec = 0;
  scale_1 = big_get_scale(*big_value_1);
  scale_2 = big_get_scale(*big_value_2);
  while (scale_1 > scale_2) {
    scale_2 += 1;
    number_dec = 1;
    s21_big_mul_by_10(*big_value_2, big_value_2);
  }
  while (scale_1 < scale_2) {
    scale_1 += 1;
    s21_big_mul_by_10(*big_value_1, big_value_1);
  }
  if (number_dec == 1)
    big_set_scale(big_value_2, scale_2);
  else
    big_set_scale(big_value_1, scale_1);
}

int conversion_big_dec_to_dec(s21_big_decimal big_value, s21_decimal *value) {
  int flag = 0;
  if (big_value.bits[3] == 0 && big_value.bits[4] == 0 &&
      big_value.bits[5] == 0) {
    for (int i = 0; i < 3; i++) {
      value->bits[i] = big_value.bits[i];
    }
    for (int i = 0; i < 3; i++) {
      value->bits[i] = big_value.bits[i];
    }
    value->bits[3] = big_value.bits[6];
  } else {
    int count_nenul_int = 0;
    int count_nenul_int_excess_1 = 0;
    s21_big_decimal big_result = {0};
    s21_big_decimal temp_big_result = {0};
    s21_big_decimal excess_1 = {0};
    s21_big_decimal excess_2 = {0};
    s21_big_decimal dec_with_value_1 = {0};
    dec_with_value_1.bits[0] = 1;
    int scale = big_get_scale(big_value);
    for (int i = 0; i < 6; i++) {
      big_result.bits[i] = big_value.bits[i];
    }
    if (scale != 0) {
      while (count_nenul_int != 3 && scale > 0) {
        if (excess_1.bits[0] != 0) count_nenul_int_excess_1++;
        s21_big_div_by_10(big_result, &big_result, &excess_1);
        scale--;
        count_nenul_int = 0;
        for (int i = 5; i >= 3; i--) {
          if (big_result.bits[i] == 0) count_nenul_int++;
        }
      }
      s21_big_div_by_10(big_result, &temp_big_result, &excess_2);
      if (excess_1.bits[0] == 5 && count_nenul_int_excess_1 == 0) {
        if (excess_2.bits[0] % 2 != 0)
          s21_big_add(big_result, dec_with_value_1, &big_result);
      } else if (excess_1.bits[0] > 5 ||
                 (excess_1.bits[0] == 5 && count_nenul_int_excess_1))
        s21_big_add(big_result, dec_with_value_1, &big_result);
    } else
      flag = 1;
    int sign = big_get_bit(big_value, 223);
    if (big_result.bits[3] != 0 || big_result.bits[4] != 0 ||
        big_result.bits[5] != 0) {
      flag = 1 + sign;
    } else {
      for (int i = 0; i < 3; i++) {
        value->bits[i] = big_result.bits[i];
      }
      set_scale(value, scale);
      set_bit(value, sign, 127);
    }
  }
  return flag;
}

void big_swapping(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2) {
  s21_big_decimal temp_1 = {0};
  s21_big_decimal temp_2 = {0};
  for (int i = 0; i < 6; i++) {
    temp_1.bits[i] = big_value_1->bits[i];
    temp_2.bits[i] = big_value_2->bits[i];
    big_value_1->bits[i] = temp_2.bits[i];
    big_value_2->bits[i] = temp_1.bits[i];
  }
}

int correct_dec(s21_decimal value) {
  int flag = 0;
  for (int i = 96; i < 112 && flag == 0; i++) {
    if (get_bit(value, i) != 0) {
      flag = 1;
    }
  }
  if (flag == 0) {
    if (get_scale(value) > 28) {
      flag = 1;
    }
  }
  for (int i = 120; i < 127 && flag == 0; i++) {
    if (get_bit(value, i) != 0) flag = 1;
  }
  return flag;
}