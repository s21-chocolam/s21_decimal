#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || correct_dec(value)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int count = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) count = 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  if (count == 0) set_bit(result, !(get_bit(value, 127)), 127);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL || correct_dec(value)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  int scale = 0;
  s21_big_decimal excess = {0};
  s21_big_decimal big_result = {0};
  for (int i = 0; i < 3; i++) {
    big_result.bits[i] = value.bits[i];
  }
  scale = get_scale(value);
  if (scale > 0) {
    for (; scale > 0; scale--) {
      s21_big_div_by_10(big_result, &big_result, &excess);
    }
    for (int i = 0; i < 3; i++) {
      result->bits[i] = big_result.bits[i];
    }
    if (result->bits[0] || result->bits[1] || result->bits[2])
      set_bit(result, get_bit(value, 127), 127);
    set_scale(result, scale);
  } else
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL || correct_dec(value)) return 1;
  s21_big_decimal big_result = {0};
  for (int i = 0; i < 3; i++) {
    big_result.bits[i] = value.bits[i];
  }
  int scale = 0;
  int sign = 0;
  int floor_flag = 0;
  scale = get_scale(value);
  sign = get_bit(value, 127);
  s21_big_decimal excess = {0};
  s21_decimal dec_with_value_1 = {0};
  dec_with_value_1.bits[0] = 1;
  if (scale > 0) {
    for (; scale > 0; scale--) {
      s21_big_div_by_10(big_result, &big_result, &excess);
      if (excess.bits[0] != 0) floor_flag++;
    }
    for (int i = 0; i < 3; i++) {
      result->bits[i] = big_result.bits[i];
    }
    if (sign == 1 && floor_flag != 0) {
      s21_add(*result, dec_with_value_1, result);
    }
    set_bit(result, get_bit(value, 127), 127);
    set_scale(result, scale);
  } else
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL || correct_dec(value)) return 1;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
  s21_big_decimal big_result = {0};
  for (int i = 0; i < 3; i++) {
    big_result.bits[i] = value.bits[i];
  }
  int scale = 0;
  scale = get_scale(value);
  s21_big_decimal excess = {0};
  s21_decimal dec_with_value_1 = {0};
  dec_with_value_1.bits[0] = 1;
  if (scale > 0) {
    for (; scale > 0; scale--) {
      s21_big_div_by_10(big_result, &big_result, &excess);
    }
    for (int i = 0; i < 3; i++) {
      result->bits[i] = big_result.bits[i];
    }
    if (excess.bits[0] >= 5) {
      s21_add(*result, dec_with_value_1, result);
    }
    set_bit(result, get_bit(value, 127), 127);
    set_scale(result, scale);
  } else
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
  return 0;
}