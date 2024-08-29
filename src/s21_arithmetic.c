#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || correct_dec(value_1) || correct_dec(value_2)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int flag = 0;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  conversion_dec_to_big_dec(value_1, &big_value_1);
  conversion_dec_to_big_dec(value_2, &big_value_2);
  normalization_decimals(&big_value_1, &big_value_2);
  s21_big_add(big_value_1, big_value_2, &big_result);
  flag = conversion_big_dec_to_dec(big_result, result);
  return flag;
}

void s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  int mat_sum_bit = 0;
  int bit_temp = 0;
  int bit_result = 0;
  int scale_result = 0;
  int bit_sign_1 = 0;
  int bit_sign_2 = 0;
  bit_sign_1 = big_get_bit(big_value_1, 223);
  bit_sign_2 = big_get_bit(big_value_2, 223);
  if (bit_sign_1 == bit_sign_2) {
    if (bit_sign_1 == 1) {
      big_set_bit(big_result, 1, 223);
    }
    for (int i = 0; i < 32 * 6; i++) {
      bit_value_1 = big_get_bit(big_value_1, i);
      bit_value_2 = big_get_bit(big_value_2, i);
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
  } else {
    if (bit_sign_1 > bit_sign_2) {
      big_set_bit(&big_value_1, 0, 223);
      s21_big_sub(big_value_2, big_value_1, big_result);
    } else {
      big_set_bit(&big_value_2, 0, 223);
      s21_big_sub(big_value_1, big_value_2, big_result);
    }
  }
  scale_result = big_get_scale(big_value_1);
  big_set_scale(big_result, scale_result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || correct_dec(value_1) || correct_dec(value_2)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int flag = 0;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  conversion_dec_to_big_dec(value_1, &big_value_1);
  conversion_dec_to_big_dec(value_2, &big_value_2);
  normalization_decimals(&big_value_1, &big_value_2);
  s21_big_sub(big_value_1, big_value_2, &big_result);
  flag = conversion_big_dec_to_dec(big_result, result);
  return flag;
}

void s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  int bit_result = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int scale = 0;
  scale = big_get_scale(big_value_1);
  sign_1 = big_get_bit(big_value_1, 223);
  sign_2 = big_get_bit(big_value_2, 223);
  if (sign_1 == sign_2) {
    if (sign_1 == 1) {
      big_swapping(&big_value_1, &big_value_2);
      big_set_bit(&big_value_1, 0, 223);
      big_set_bit(&big_value_2, 0, 223);
    }
    if (s21_big_is_less(big_value_1, big_value_2)) {
      big_swapping(&big_value_1, &big_value_2);
      big_set_bit(big_result, 1, 223);
    }
    for (int i = 0; i < 32 * 6; i++) {
      bit_value_1 = big_get_bit(big_value_1, i);
      bit_value_2 = big_get_bit(big_value_2, i);
      if (bit_value_1 == 1 && bit_value_2 == 1) bit_result = 0;
      if (bit_value_1 == 0 && bit_value_2 == 1) {
        int j = i;
        while (big_get_bit(big_value_1, j) != 1) {
          big_set_bit(&big_value_1, 1, j);
          j++;
        }
        big_set_bit(&big_value_1, 0, j);
        bit_result = 1;
      }
      if (bit_value_1 == 1 && bit_value_2 == 0) bit_result = 1;
      if (bit_value_1 == 0 && bit_value_2 == 0) bit_result = 0;
      big_set_bit(big_result, bit_result, i);
    }
  } else if (sign_1 > sign_2) {
    big_set_bit(&big_value_1, 0, 223);
    s21_big_add(big_value_1, big_value_2, big_result);
    big_set_bit(big_result, 1, 223);
  } else {
    big_set_bit(&big_value_2, 0, 223);
    s21_big_add(big_value_1, big_value_2, big_result);
  }
  big_set_scale(big_result, scale);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || correct_dec(value_1) || correct_dec(value_2)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int flag = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_result = 0;
  if (value_2.bits[0] || value_2.bits[1] || value_2.bits[2]) {
    sign_1 = get_bit(value_1, 127);
    sign_2 = get_bit(value_2, 127);
    sign_result = sign_1 + sign_2;
    if (sign_result == 2) sign_result = 0;
    s21_big_decimal big_value_1 = {0};
    s21_big_decimal big_value_2 = {0};
    s21_big_decimal big_result = {0};
    conversion_dec_to_big_dec(value_1, &big_value_1);
    conversion_dec_to_big_dec(value_2, &big_value_2);
    s21_big_div(big_value_1, big_value_2, &big_result);
    big_set_bit(&big_result, sign_result, 223);
    flag = conversion_big_dec_to_dec(big_result, result);
  } else
    flag = 3;
  return flag;
}

void s21_big_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  int number_shift_left = 0;
  s21_big_decimal temp = {0};
  s21_big_decimal excess_wp = {0};
  s21_big_decimal whole_part = {0};
  s21_big_decimal mull_excess_by_10 = {0};
  s21_big_decimal excess_fp = {0};
  s21_big_decimal fractional_part = {0};
  s21_big_decimal result_fractional_part = {0};
  int count = 0;
  int count_scale = 0;
  for (int i = 0; i < 6; i++) {
    temp.bits[i] = big_value_2.bits[i];
    excess_wp.bits[i] = big_value_1.bits[i];
  }
  calculation_of_excess_div(&temp, &excess_wp, &whole_part, big_value_1,
                            big_value_2, &number_shift_left);
  for (int i = 0; i < 6; i++) {
    big_result->bits[i] = whole_part.bits[i];
  }

  int zero_excess_flag = 0;
  for (int i = 0; i < 6; i++) {
    if (excess_wp.bits[i] != 0) zero_excess_flag++;
  }
  int count_nenul_int = 0;
  int scale_1 = 0;
  int scale_2 = 0;
  int scale_result = 0;
  scale_1 = big_get_scale(big_value_1);
  scale_2 = big_get_scale(big_value_2);

  if (zero_excess_flag > 0) {
    excess_fp.bits[0] = 1;
    s21_big_mul_by_10(excess_wp, &mull_excess_by_10);
    while (zero_excess_flag > 0 && count_scale < 29) {
      zero_excess_flag = 0;
      if (count != 0) s21_big_mul_by_10(excess_fp, &mull_excess_by_10);
      for (int i = 0; i < 6; i++) {
        excess_fp.bits[i] = mull_excess_by_10.bits[i];
      }
      number_shift_left = 0;
      calculation_of_excess_div(&temp, &excess_fp, &fractional_part,
                                mull_excess_by_10, big_value_2,
                                &number_shift_left);
      s21_big_mul_by_10(result_fractional_part, &result_fractional_part);
      s21_big_add(result_fractional_part, fractional_part,
                  &result_fractional_part);
      for (int i = 0; i < 6; i++) {
        fractional_part.bits[i] = 0;
      }
      for (int i = 0; i < 6; i++) {
        if (excess_fp.bits[i] != 0) zero_excess_flag++;
      }
      for (int i = 0; i < 6; i++) {
        if (result_fractional_part.bits[i] != 0) count_nenul_int++;
      }
      if (count_nenul_int > 1) count_scale++;
      count++;
    }
  }
  for (int i = 1; i <= count; i++) {
    s21_big_mul_by_10(*big_result, big_result);
  }
  s21_big_add(*big_result, result_fractional_part, big_result);
  scale_result = scale_1 - scale_2;
  if (scale_result < 0) {
    while (count > 0 && scale_result < 0) {
      count--;
      scale_result++;
    }
    while (count == 0 && scale_result < 0) {
      s21_big_mul_by_10(*big_result, big_result);
      scale_result++;
    }
    scale_result = scale_result + count;
    big_set_scale(big_result, scale_result);
  } else {
    scale_result = scale_result + count;
    big_set_scale(big_result, scale_result);
  }
}

void calculation_of_excess_div(s21_big_decimal *temp, s21_big_decimal *excess,
                               s21_big_decimal *whole_or_fractional_part,
                               s21_big_decimal big_value_1,
                               s21_big_decimal big_value_2,
                               int *number_shift_left) {
  s21_big_decimal temp_big_value_1 = {0};
  for (int i = 0; i < 6; i++) {
    temp_big_value_1.bits[i] = big_value_1.bits[i];
  }
  while (s21_big_is_less_or_equal(*temp, temp_big_value_1)) {
    big_shift_left(temp, 1);
    (*number_shift_left)++;
  }
  *number_shift_left = *number_shift_left - 1;
  for (int i = 0; i < 6; i++) {
    temp->bits[i] = big_value_2.bits[i];
  }
  for (int i = *number_shift_left; i >= 0; i--) {
    big_shift_left(temp, i);
    if (s21_big_is_less_or_equal(*temp, *excess)) {
      big_set_bit(whole_or_fractional_part, 1, i);
    } else {
      big_set_bit(whole_or_fractional_part, 0, i);
      for (int i = 0; i < 6; i++) {
        temp->bits[i] = 0;
      }
    }
    if (s21_big_is_less_or_equal(*temp, *excess))
      s21_big_sub(*excess, *temp, excess);
    for (int i = 0; i < 6; i++) {
      temp->bits[i] = big_value_2.bits[i];
    }
  }
}

void s21_big_div_by_10(s21_big_decimal big_value_1, s21_big_decimal *big_result,
                       s21_big_decimal *excess) {
  int number_shift_left = 0;
  s21_big_decimal temp = {0};
  s21_big_decimal whole_part = {0};
  s21_big_decimal dec_with_value_10 = {0};
  dec_with_value_10.bits[0] = 10;

  for (int i = 0; i < 6; i++) {
    temp.bits[i] = dec_with_value_10.bits[i];
    excess->bits[i] = big_value_1.bits[i];
  }
  calculation_of_excess_div(&temp, excess, &whole_part, big_value_1,
                            dec_with_value_10, &number_shift_left);
  for (int i = 0; i < 6; i++) {
    big_result->bits[i] = whole_part.bits[i];
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || correct_dec(value_1) || correct_dec(value_2)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int flag = 0;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  conversion_dec_to_big_dec(value_1, &big_value_1);
  conversion_dec_to_big_dec(value_2, &big_value_2);
  s21_big_mul(big_value_1, big_value_2, &big_result);
  flag = conversion_big_dec_to_dec(big_result, result);
  return flag;
}

void s21_big_mul(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  int scale_1 = 0;
  int scale_2 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_result = 0;
  sign_1 = big_get_bit(big_value_1, 223);
  sign_2 = big_get_bit(big_value_2, 223);
  sign_result = sign_1 + sign_2;
  if (sign_result == 2) sign_result = 0;
  int scale_result = 0;
  scale_1 = big_get_scale(big_value_1);
  scale_2 = big_get_scale(big_value_2);
  scale_result = scale_1 + scale_2;

  int bit_value_1 = 0;
  s21_big_decimal mat_sum = {0};
  s21_big_decimal temp_2 = {0};
  for (int i = 0; i < 6; i++) {
    temp_2.bits[i] = big_value_2.bits[i];
  }

  for (int i = 0; i < 32 * 6; i++) {
    bit_value_1 = big_get_bit(big_value_1, i);
    if (bit_value_1 == 1) {
      big_shift_left(&temp_2, i);
      s21_big_add(mat_sum, temp_2, &mat_sum);
    }
    for (int i = 0; i < 6; i++) {
      temp_2.bits[i] = big_value_2.bits[i];
    }
    big_set_scale(&mat_sum, scale_result);
    for (int i = 0; i < 7; i++) {
      big_result->bits[i] = mat_sum.bits[i];
    }
    big_set_bit(big_result, sign_result, 223);
  }
}
