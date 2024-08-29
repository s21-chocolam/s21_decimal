#include "./s21_decimal_tests.h"

void test_negate(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result = {0};

  int is_error = s21_negate(decimal, &result);
  int sign_check = get_bit(decimal_check, 127);
  int sign_result = get_bit(result, 127);

  ck_assert_int_eq(is_error, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(test_negate_1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_5) {
  // 52818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_6) {
  // -52818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_7) {
  // 12297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
  // -12297829382473034410
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_8) {
  // -12297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
  // 12297829382473034410
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_9) {
  // 1229782938247303441.0
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
  // -1229782938247303441.0
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_10) {
  // -1229782938247303441.0
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
  // 1229782938247303441.0
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_11) {
  // 1.2297829379609722880
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
  // -1.2297829379609722880
  s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_12) {
  // -1.2297829379609722880
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 1.2297829379609722880
  s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_13) {
  // 1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_14) {
  // -1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_15) {
  // 0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_16) {
  // -0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_17) {
  // 0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
  // -0.0000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x800D0000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_18) {
  // -0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
  // 0.0000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0xD0000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_19) {
  // 0.000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
  // -0.000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

  test_negate(decimal, decimal_check);
}

START_TEST(test_negate_20) {
  // -0.000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
  // 0.000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

  test_negate(decimal, decimal_check);
}

Suite *negate_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("negate_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_negate_1);
  tcase_add_test(tc_core, test_negate_2);
  tcase_add_test(tc_core, test_negate_3);
  tcase_add_test(tc_core, test_negate_4);
  tcase_add_test(tc_core, test_negate_5);
  tcase_add_test(tc_core, test_negate_6);
  tcase_add_test(tc_core, test_negate_7);
  tcase_add_test(tc_core, test_negate_8);
  tcase_add_test(tc_core, test_negate_9);
  tcase_add_test(tc_core, test_negate_10);
  tcase_add_test(tc_core, test_negate_11);
  tcase_add_test(tc_core, test_negate_12);
  tcase_add_test(tc_core, test_negate_13);
  tcase_add_test(tc_core, test_negate_14);
  tcase_add_test(tc_core, test_negate_15);
  tcase_add_test(tc_core, test_negate_16);
  tcase_add_test(tc_core, test_negate_17);
  tcase_add_test(tc_core, test_negate_18);
  tcase_add_test(tc_core, test_negate_19);
  tcase_add_test(tc_core, test_negate_20);
  suite_add_tcase(s, tc_core);
  return s;
}