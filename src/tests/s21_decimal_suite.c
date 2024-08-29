#include "s21_decimal_tests.h"
// #include "conversion_decimal_to_float_tests.c"
// #include "conversion_decimal_to_int_tests.c"
// #include "conversion_float_to_decimal_tests.c"
// #include "conversion_int_to_decimal_tests.c"
// #include "s21_add_tests.c"
// #include "s21_div_tests.c"
// #include "s21_floor_tests.c"
// #include "s21_is_equal_tests.c"
// #include "s21_is_greater_or_equal_tests.c"
// #include "s21_is_greater_tests.c"
// #include "s21_is_less_or_equal_tests.c"
// #include "s21_is_less_tests.c"
// //#include "s21_is_not_equal_tests.c"
// #include "s21_mul_tests.c"
// #include "s21_negate_tests.c"
// #include "s21_round_tests.c"
// #include "s21_sub_tests.c"
// #include "s21_truncate_tests.c"

int main(void) {
  run_tests();
  return 0;
}

void run_tests(void) {
  Suite* list_cases[] = {

      suite_s21_from_int_to_decimal(),
      suite_s21_from_decimal_to_int(),
      suite_float_to_decimal(),
      suite_s21_from_decimal_to_float(),
      suite_s21_mul(),
      suite_s21_div(),
      s21_add_cases(),
      s21_sub_cases(),
      floor_suite(),
      round_suite(),
      suite_truncate(),
      negate_suite(),
      suite_s21_is_equal_test(),
      suite_s21_is_not_equal_test(),
      suite_s21_is_greater_test(),
      suite_s21_is_greater_or_equal_test(),
      suite_s21_is_less_test(),
      suite_s21_is_less_or_equal_test(),
      NULL};
  for (Suite** current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite* testcase) {
  static int counter_testcase = 1;
  if (counter_testcase > 1) putchar('\n');
  printf("CURRENT TEST: %d\n", counter_testcase);
  counter_testcase++;

  SRunner* sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

// START_TEST(s21_div_test) {
//   s21_decimal dec_1 = {{0, 0, 0, 0}};
//   dec_1.bits[0] = dec_1.bits[1] = dec_1.bits[2] = UINT_MAX;
//   s21_decimal dec_2 = {{2, 0, 0, 0}};  // 0.2
//   s21_set_dec_scale(&dec_2, 1);
//   s21_decimal result = {{0, 0, 0, 0}};

//   s21_decimal dec_2_minus = {{2, 0, 0, 0}};  // -0.2
//   s21_set_dec_scale(&dec_2_minus, 1);
//   s21_set_dec_bit(&dec_2_minus, 127, 1);
//   s21_decimal dec_zero = {{0, 0, 0, 0}};

//   ck_assert_int_eq(s21_div(dec_1, dec_2, &result), 1);        // +infinity
//   ck_assert_int_eq(s21_div(dec_1, dec_2_minus, &result), 2);  // -infinity
//   ck_assert_int_eq(s21_div(dec_1, dec_zero, &result), 3);
//   ck_assert_int_eq(s21_div(dec_2, dec_2_minus, &result), 0);  // -1

//   s21_bigdecimal result_minus_1 = {{1, 0, 0, 0, 0, 0, 0, 0}};
//   s21_set_dec_bit(&dec_2_minus, 127, 1);  // -1

//   s21_bigdecimal result_expected = {{1, 0, 0, 0, 0, 0, 0, 0}};
//   s21_set_bigdec_bit(&result_expected, 225, 1);
//   s21_dec_to_bigdec(&result_minus_1, result);
//   ck_assert_int_eq(s21_bigdec_cmp_mantissa(result_expected, result_minus_1),
//   0);
// }
// END_TEST

// START_TEST(s21_mul_test) {
//   s21_decimal dec_1 = {{0, 0, 0, 0}};
//   dec_1.bits[0] = dec_1.bits[1] = dec_1.bits[2] = UINT_MAX;
//   s21_decimal dec_2 = {{2, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_decimal dec_2_minus = {{2, 0, 0, 0}};  // -2
//   s21_set_dec_bit(&dec_2_minus, 127, 1);

//   ck_assert_int_eq(s21_mul(dec_1, dec_2, &result), 1);        // +infinity
//   ck_assert_int_eq(s21_mul(dec_1, dec_2_minus, &result), 2);  // -infinity
//   ck_assert_int_eq(s21_mul(dec_2, dec_2_minus, &result), 0);

//   s21_bigdecimal big_result = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   s21_bigdecimal result_2_expected = {{4, 0, 0, 0, 0, 0, 0, 0}};
//   s21_set_bigdec_bit(&result_2_expected, 225, 1);  // -4
//   s21_dec_to_bigdec(&big_result, result);
//   ck_assert_int_eq(
//       s21_bigdec_cmp_mantissa(result_2_expected, result_2_expected), 0);
// }
// END_TEST

// Suite* suite_s21_main_functions_tests(void) {
//   Suite* s = suite_create("s21_main_functions_tests");
//   TCase* tc = tcase_create("s21_main_functions_tests_tc");

//   tcase_add_test(tc, s21_div_test);
//   tcase_add_test(tc, s21_mul_test);

//   suite_add_tcase(s, tc);
//   return s;
// }
