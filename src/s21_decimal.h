#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

int s21_from_int_to_decimal(int src, s21_decimal *value);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_big_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);
void s21_big_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);
void s21_big_mul(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);
void s21_big_div(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);
void calculation_of_excess_div(s21_big_decimal *temp, s21_big_decimal *excess,
                               s21_big_decimal *whole_or_fractional_part,
                               s21_big_decimal big_value_1,
                               s21_big_decimal big_value_2,
                               int *number_shift_left);
void s21_mul_by_10(s21_decimal value, s21_decimal *result);
void s21_big_mul_by_10(s21_big_decimal big_value, s21_big_decimal *big_result);
void s21_div_by_10(s21_decimal value_1, s21_decimal *result,
                   s21_decimal *excess);
void s21_big_div_by_10(s21_big_decimal big_value_1, s21_big_decimal *big_result,
                       s21_big_decimal *excess);

int s21_big_is_less(s21_big_decimal big_value_1, s21_big_decimal big_value_2);
int s21_big_is_less_or_equal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_big_is_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2);

void print_decimal(s21_decimal value);
void print_big_decimal(s21_big_decimal big_value);
int get_bit(s21_decimal value, int index);
int big_get_bit(s21_big_decimal big_value, int index);
void set_bit(s21_decimal *value, int bit, int index);
void big_set_bit(s21_big_decimal *big_value, int bit, int index);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
int big_get_scale(s21_big_decimal value);
void big_set_scale(s21_big_decimal *value, int scale);
void conversion_dec_to_big_dec(s21_decimal value, s21_big_decimal *big_value);
int conversion_big_dec_to_dec(s21_big_decimal big_value, s21_decimal *value);
void normalization_decimals(s21_big_decimal *big_value_1,
                            s21_big_decimal *big_value_2);
void shift_left(s21_decimal *value, int number_shift_left);
void big_shift_left(s21_big_decimal *big_value, int number_shift_left);
void swapping(s21_decimal *value_1, s21_decimal *value_2);
void big_swapping(s21_big_decimal *big_value_1, s21_big_decimal *big_value_2);
int correct_dec(s21_decimal value);

#endif