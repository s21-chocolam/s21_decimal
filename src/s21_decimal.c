#include "s21_decimal.h"

int main() {
  int val = 4;
  int val_1 = 250;
  int val_2 = 5;
  int scale_1 = 0;
  int scale_2 = 28;
  // float src = 123.41523671;
  s21_decimal value_dec = {0};
  s21_decimal value_dec_1 = {0};
  // set_scale(&value_dec_1, scale_1);
  //  value_dec_1.bits[0] = 57;
  //  value_dec_1.bits[1] = 67;
  s21_decimal value_dec_2 = {0};
  s21_decimal dec_1 = {0};
  // s21_decimal dec_2 = {0};
  s21_big_decimal value_big_dec = {0};
  s21_decimal result = {0};
  //  s21_decimal result_2 = {0};
  s21_from_int_to_decimal(val, &value_dec);
  s21_from_int_to_decimal(val_1, &value_dec_1);
  s21_from_int_to_decimal(val_2, &value_dec_2);
  set_scale(&value_dec_1, scale_1);
  set_scale(&value_dec_2, scale_2);
  conversion_dec_to_big_dec(value_dec, &value_big_dec);
  // shift_right(&value_dec, 2);
  //  print_decimal(value_dec);
  //  s21_add(value_dec_1, value_dec_2, &result);
  //  printf("Sum_dec_1_and_dec_2: ");
  //  print_decimal(result);
  //  printf("\ndec_1: ");
  //  print_decimal(value_dec_1);
  //  printf("\ndec_2: ");
  //  print_decimal(value_dec_2);
  //  s21_sub(value_dec_1, value_dec_2, &result);
  //  printf("sub_dec_1_dec_2: ");
  //  print_decimal(result);
  //     printf("status dec_1 = dec_2: %d\n",
  //            s21_is_equal(value_dec_1, value_dec_2));
  //     printf("status dec_1 < dec_2: %d\n", s21_is_less(value_dec_1,
  //     value_dec_2)); printf("status dec_1 <= dec_2: %d\n",
  //            s21_is_less_or_equal(value_dec_1, value_dec_2));
  //     printf("status dec_1 > dec_2: %d\n",
  //            s21_is_greater(value_dec_1, value_dec_2));
  //     printf("status dec_1 >= dec_2: %d\n",
  //            s21_is_greater_or_equal(value_dec_1, value_dec_2));
  //     printf("status dec_1 = dec_2: %d\n",
  //            s21_is_equal(value_dec_1, value_dec_2));
  //     printf("status dec_1 != dec_2: %d\n",
  //            s21_is_not_equal(value_dec_1, value_dec_2));

  // print_big_decimal(&value_big_dec);
  // printf("%d\n", s21_from_float_to_decimal(src, &result));
  //   s21_decimal dec_1 = {{0x143, 0x0, 0x0, 0x0}};
  //   // 655
  //   s21_decimal dec_2 = {{0x28f, 0x0, 0x0, 0x0}};
  // s21_decimal dec_check = {{0x33a6d, 0x0, 0x0, 0x0}};
  // s21_negate(value_dec, &result);
  // set_scale(&value_dec, 29);
  // set_bit(&value_dec, 1, 125);
  // print_decimal(value_dec);
  // printf("%d\n", correct_scale(value_dec));
  // print_decimal(value_dec_1);
  // print_decimal(value_dec_2);
  // s21_div(value_dec_1, value_dec_2, &result);
  // printf("%d\n", s21_from_float_to_decimal());
  // s21_mul(dec_1, dec_2, &result);
  // s21_add(dec_1, dec_2, &result);
  // s21_sub(dec_1, dec_2, &result);
  // s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};

  // s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}};

  // s21_sub(dec_1, dec_2, &result);
  // s21_div(dec_1, dec_2, &result);
  //  s21_truncate(value_dec_2, &result);
  //  s21_floor(value_dec_2, &result);
  // s21_round(decimal, &result);
  //  s21_from_decimal_to_int(value_dec_2, &val);
  //  s21_from_decimal_to_float(value_dec_2, &a);
  // print_decimal(decimal);
  //  print_decimal(dec_2);
  //  printf("%f\n", 53943.9483);
  //  printf("%f\n", a);
  // s21_decimal dec_1 = {{10, 0, 0, 0}};  // 0.1
  // set_scale(&dec_1, 1);
  // s21_decimal dec_2 = {{50, 0, 0, 0}};  // -0.5
  // set_scale(&dec_2, 1);
  // set_bit(&dec_2, 127, 1);

  // s21_decimal dec_check = {{2, 0, 0, 0}};
  // set_scale(&dec_check, 1);
  // set_bit(&dec_check, 127, 1);
  //   print_decimal(dec_1);
  //   print_decimal(dec_2);
  //   s21_div(dec_1, dec_2, &result);
  dec_1.bits[0] = 0b00000000000000000000000000110010;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000010000000000000000;

  result.bits[0] = 0b00000000000000000000000000000101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  print_decimal(dec_1);
  s21_floor(dec_1, &result);
  print_decimal(result);

  return 0;
}