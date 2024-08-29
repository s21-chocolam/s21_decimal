#include "s21_decimal_tests.h"

START_TEST(test_equal_zero) {
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal a = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_zero_and_non_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_equal_max_values) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal b = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_max_and_min_values) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_not_equal_with_different_scale) {
  s21_decimal a = {{1, 0, 0, 0x00010000}};  // 1e-1
  s21_decimal b = {{1, 0, 0, 0}};           // 1

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_equal_with_scale) {
  s21_decimal a = {{1000000, 0, 0, 0x00060000}};  // 1.000000 (scale 6)
  s21_decimal b = {{1, 0, 0, 0}};                 // 1

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_negative_values) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal b = {{1, 0, 0, 0x80000000}};  // -1
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_negative_and_positive_values) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal b = {{1, 0, 0, 0}};           // 1
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_equal_negative_with_scale) {
  s21_decimal a = {{1000000, 0, 0, 0x80060000}};  // -1.000000 (scale 6)
  s21_decimal b = {{1, 0, 0, 0b10000000000000000000000000000000}};  // -1
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_different_representation_same_value) {
  s21_decimal a = {{5000, 0, 0, 0x00020000}};   // 50.00 (scale 2)
  s21_decimal b = {{50000, 0, 0, 0x00030000}};  // 50.000 (scale 3)
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_with_scale_different_representation) {
  s21_decimal a = {{500000, 0, 0, 0x00050000}};  // 5.00000 (scale 5)
  s21_decimal b = {{5, 0, 0, 0}};                // 5
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_large_scale_difference) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};  // 1e-28
  s21_decimal b = {{1, 0, 0, 0}};           // 1
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal a = {{100, 0, 0, 0x00010000}};  // 10
  s21_decimal b = {{10, 0, 0, 0}};            // 10
  ck_assert_int_eq(s21_is_equal(a, b), 1);

  s21_decimal c = {{123456789, 0, 0, 0x00020000}};  // 1234567.89
  s21_decimal d = {{123456789, 0, 0, 0x00020000}};  // 1234567.89
  ck_assert_int_eq(s21_is_equal(c, d), 1);

  s21_decimal e = {{1, 0, 0, 0x00000000}};  // 1
  s21_decimal f = {{2, 0, 0, 0x00000000}};  // 2
  ck_assert_int_eq(s21_is_equal(e, f), 0);
}
END_TEST

START_TEST(test_equal_zero_and_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_zero_and_zero_with_scale) {
  s21_decimal a = {{0, 0, 0, 0x00010000}};  // 0 with scale 1
  s21_decimal b = {{0, 0, 0, 0}};           // 0
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_negative_zero_and_zero_with_scale) {
  s21_decimal a = {{0, 0, 0, 0x80010000}};  // -0 with scale 1
  s21_decimal b = {{0, 0, 0, 0}};           // 0
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

Suite* suite_s21_is_equal_test(void) {
  Suite* s = suite_create("s21_is_equal");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_equal_zero);
  tcase_add_test(tc_core, test_not_equal_zero_and_non_zero);
  tcase_add_test(tc_core, test_equal_max_values);
  tcase_add_test(tc_core, test_not_equal_max_and_min_values);
  tcase_add_test(tc_core, test_equal_with_scale);
  tcase_add_test(tc_core, test_not_equal_with_different_scale);
  tcase_add_test(tc_core, test_equal_with_scale);
  tcase_add_test(tc_core, test_s21_is_equal);
  tcase_add_test(tc_core, test_not_equal_with_different_scale);
  tcase_add_test(tc_core, test_equal_negative_values);
  tcase_add_test(tc_core, test_not_equal_negative_and_positive_values);
  tcase_add_test(tc_core, test_equal_negative_with_scale);
  tcase_add_test(tc_core, test_equal_different_representation_same_value);
  tcase_add_test(tc_core, test_not_equal_large_scale_difference);
  tcase_add_test(tc_core, test_equal_with_scale_different_representation);
  tcase_add_test(tc_core, test_equal_zero_and_negative_zero);
  tcase_add_test(tc_core, test_equal_zero_and_zero_with_scale);
  tcase_add_test(tc_core, test_equal_negative_zero_and_zero_with_scale);

  suite_add_tcase(s, tc_core);

  return s;
}
