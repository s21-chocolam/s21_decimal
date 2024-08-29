#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (correct_dec(value_1) || correct_dec(value_2)) return 1;
  int flag = 0;
  int sign_1 = get_bit(value_1, 127);
  int sign_2 = get_bit(value_2, 127);
  if (sign_1 == sign_2) {
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);
    if (scale_1 != scale_2) {
      s21_big_decimal big_value_1 = {0};
      s21_big_decimal big_value_2 = {0};
      conversion_dec_to_big_dec(value_1, &big_value_1);
      conversion_dec_to_big_dec(value_2, &big_value_2);
      normalization_decimals(&big_value_1, &big_value_2);
      flag = s21_big_is_less(big_value_1, big_value_2);
    } else {
      for (int i = 2; i >= 0; i--) {
        if (((value_1.bits[i] < value_2.bits[i]) && sign_1 == 0) ||
            ((value_1.bits[i] > value_2.bits[i]) && sign_1 == 1)) {
          flag = 1;
          break;
        } else if (value_1.bits[i] != value_2.bits[i])
          break;
      }
    }
  } else if (sign_1 > sign_2)
    flag = 1;
  return flag;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (correct_dec(value_1) || correct_dec(value_2)) return 1;
  int flag = 0;
  if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) flag = 1;
  return flag;
}

int s21_big_is_less_or_equal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2) {
  int flag = 0;
  if (s21_big_is_less(big_value_1, big_value_2) ||
      s21_big_is_equal(big_value_1, big_value_2))
    flag = 1;
  return flag;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  if (correct_dec(value_1) || correct_dec(value_2)) return 1;
  int flag = 0;
  if (!s21_is_less(value_1, value_2) && !s21_is_equal(value_1, value_2))
    flag = 1;
  return flag;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (correct_dec(value_1) || correct_dec(value_2)) return 1;
  int flag = 0;
  if (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2))
    flag = 1;
  return flag;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (correct_dec(value_1) || correct_dec(value_2)) return 1;
  int flag = 1;
  int count_nul_int = 0;
  int sign_1 = get_bit(value_1, 127);
  int sign_2 = get_bit(value_2, 127);
  if (sign_1 == sign_2) {
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);
    if (scale_1 != scale_2) {
      s21_big_decimal big_value_1 = {0};
      s21_big_decimal big_value_2 = {0};
      conversion_dec_to_big_dec(value_1, &big_value_1);
      conversion_dec_to_big_dec(value_2, &big_value_2);
      normalization_decimals(&big_value_1, &big_value_2);
      flag = s21_big_is_equal(big_value_1, big_value_2);
    } else {
      for (int i = 2; i >= 0; i--) {
        if (value_1.bits[i] != value_2.bits[i]) {
          flag = 0;
          break;
        }
      }
    }
  } else {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] == 0 && value_2.bits[i] == 0) {
        count_nul_int++;
      }
    }
    if (count_nul_int != 3) flag = 0;
  }
  return flag;
}

int s21_big_is_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2) {
  int flag = 1;
  for (int i = 5; i >= 0; i--) {
    if (big_value_1.bits[i] != big_value_2.bits[i]) {
      flag = 0;
      break;
    }
  }
  return flag;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_big_is_less(s21_big_decimal big_value_1, s21_big_decimal big_value_2) {
  int flag = 0;
  int sign_1 = big_get_bit(big_value_1, 223);
  for (int i = 5; i >= 0; i--) {
    if (((big_value_1.bits[i] < big_value_2.bits[i]) && sign_1 == 0) ||
        ((big_value_1.bits[i] > big_value_2.bits[i]) && sign_1 == 1)) {
      flag = 1;
      break;
    } else if (big_value_1.bits[i] != big_value_2.bits[i])
      break;
  }
  return flag;
}