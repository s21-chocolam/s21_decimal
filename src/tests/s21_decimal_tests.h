#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite* suite_s21_main_functions_tests(void);
Suite* suite_s21_bit_functions_tests(void);
Suite* suite_s21_common_functions_tests(void);
Suite* suite_s21_conversion_functions_tests(void);
Suite* suite_s21_from_int_to_decimal(void);
Suite* suite_s21_from_decimal_to_int(void);
Suite* suite_float_to_decimal(void);
Suite* suite_s21_from_decimal_to_float(void);

Suite* suite_s21_mul(void);
Suite* suite_s21_div(void);
Suite* s21_add_cases(void);
Suite* s21_sub_cases(void);

Suite* floor_suite(void);
Suite* round_suite(void);
Suite* suite_truncate(void);
Suite* negate_suite(void);

Suite* suite_s21_is_equal_test(void);
Suite* suite_s21_is_greater_or_equal_test(void);
Suite* suite_s21_is_greater_test(void);
Suite* suite_s21_is_less_test(void);
Suite* suite_s21_is_less_or_equal_test(void);
Suite* suite_s21_is_not_equal_test(void);

void run_tests(void);
void run_testcase(Suite* testcase);

#endif  // TESTS_H
