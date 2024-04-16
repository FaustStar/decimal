#include <check.h>
#include <stdlib.h>
#include "s21_decimal.h"

// -------------------------------------------------- ARITHMETIC --------------------------------------------------

// -------------------------------------------------- add() --------------------------------------------------

START_TEST(test_add_1) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{200, 0, 0, 0x00000000}};
  s21_decimal check_res = {{300, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_2) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{100, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_3) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{100, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_4) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{300, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_5) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_6) {
  // 7.92281625142643375935439503
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 11.884224377139650639031592551
  s21_decimal check_res = {{0x66666667, 0x66666666, 0x26666666, 0x1B0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  s21_decimal check_res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  s21_decimal check_res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555302
  s21_decimal check_res = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_12) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_16) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_add_17) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950326
  s21_decimal check_res = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_18) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_19) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950333
  s21_decimal check_res = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_20) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_add_21) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

// -------------------------------------------------- sub() --------------------------------------------------

START_TEST(test_sub_1) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{100, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_2) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x00000000}};
  s21_decimal check_res = {{300, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_3) {
  s21_decimal decimal1 = {{200, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{300, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_4) {
  s21_decimal decimal1 = {{200, 0, 0, 0x80000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{100, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_5) {
  s21_decimal decimal1 = {{100, 0, 0, 0x00000000}};
  s21_decimal decimal2 = {{100, 0, 0, 0x80000000}};
  s21_decimal check_res = {{200, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_6) {
  // 7.92281625142643375935439503
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 3.9614081257132168796771975172
  s21_decimal check_res = {{0x4, 0x0, 0x80000000, 0x1C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal check_res = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_12) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_13) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_14) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(decimal1, decimal2, &res));
}
END_TEST

START_TEST(test_sub_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_17) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -79228162514264337593517540948
  s21_decimal check_res = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_18) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950333
  s21_decimal check_res = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_19) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check_res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_20) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

START_TEST(test_sub_21) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check_res = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(decimal1, decimal2, &res));
  ck_assert_int_eq(res.bits[0], check_res.bits[0]);
  ck_assert_int_eq(res.bits[1], check_res.bits[1]);
  ck_assert_int_eq(res.bits[2], check_res.bits[2]);
  ck_assert_int_eq(res.bits[3], check_res.bits[3]);
}
END_TEST

// -------------------------------------------------- mul() --------------------------------------------------



// -------------------------------------------------- div() --------------------------------------------------

// -------------------------------------------------- COMPARISON --------------------------------------------------

// -------------------------------------------------- is_less() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_less_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_less_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_less_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_less_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_less_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_less_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_less_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_less_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_less_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_less_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less(value_1, value_2));
}
END_TEST

// -------------------------------------------------- is_less_or_equal() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_less_or_equal_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_less_or_equal_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_less_or_equal_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_less_or_equal_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_less_or_equal_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_less_or_equal_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_less_or_equal_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_less_or_equal_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_less_or_equal_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_less_or_equal_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_less_or_equal_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

// -------------------------------------------------- is_greater() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_greater_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_greater_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_greater_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_greater_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_greater_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_greater_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_greater_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_greater_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_greater_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_greater_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

// -------------------------------------------------- is_greater_or_equal() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_greater_or_equal_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_greater_or_equal_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_greater_or_equal_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_greater_or_equal_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_greater_or_equal_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_greater_or_equal_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_greater_or_equal_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_greater_or_equal_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_greater_or_equal_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_greater_or_equal_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_greater_or_equal_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

// -------------------------------------------------- is_equal() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_equal_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_equal_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_equal_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_equal_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_equal_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_equal_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_equal_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_equal_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_equal_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_equal_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_equal_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_equal(value_1, value_2));
}
END_TEST

// -------------------------------------------------- is_not_equal() --------------------------------------------------

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_2) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_3) {
  s21_decimal value_1 = {{135, 0, 0, 0}};
  s21_decimal value_2 = {{0, 15, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_4) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_5) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (sign and exponent are equal in 1 and 2)
START_TEST(test_not_equal_6) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 is negative, 2 is positive)
START_TEST(test_not_equal_7) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b00000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (2 is negative, 1 is positive)
START_TEST(test_not_equal_8) {
    s21_decimal value_1;
    value_1.bits[0] = 0b10000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b00000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000111000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 == 2 (1 and 2 are negative)
START_TEST(test_not_equal_9) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000000110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000000110000000000000000;
    ck_assert_int_eq(FALSE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative)
START_TEST(test_not_equal_10) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b00000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000100100000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative)
START_TEST(test_not_equal_11) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11000000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001110000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b00000000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are negative, exponent is different)
START_TEST(test_not_equal_12) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are negative, exponent is different)
START_TEST(test_not_equal_13) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b10000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b10000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (1 and 2 are positive, exponent is different)
START_TEST(test_not_equal_14) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000011010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 > 2 (1 and 2 are positive, exponent is different)
START_TEST(test_not_equal_15) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000001010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11010000000000000000000000000000;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

// 1 < 2 (2 is much bigger than 1)
START_TEST(test_not_equal_16) {
    s21_decimal value_1;
    value_1.bits[0] = 0b00000000000000000000000000100001;
    value_1.bits[1] = 0b00000000000000000000000000000000;
    value_1.bits[2] = 0b11010000000000000000000000000000;
    value_1.bits[3] = 0b00000000000111010000000000000000;

    s21_decimal value_2;
    value_2.bits[0] = 0b00000000000000000000000000100001;
    value_2.bits[1] = 0b00000000000000000000000000000000;
    value_2.bits[2] = 0b11111111111111111111111111111110;
    value_2.bits[3] = 0b00000000000001110000000000000000;
    ck_assert_int_eq(TRUE, s21_is_not_equal(value_1, value_2));
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s;
  /*TCase *tc_core_add;
  TCase *tc_core_sub;
  TCase *tc_core_mul;
  TCase *tc_core_div;*/
  TCase *tc_core_less;
  TCase *tc_core_less_or_equal;
  TCase *tc_core_greater;
  TCase *tc_core_greater_or_equal;
  TCase *tc_core_equal;
  TCase *tc_core_not_equal;
  /*TCase *tc_core_from_int_to_decimal;
  TCase *tc_core_from_float_to_decimal;
  TCase *tc_core_from_decimal_to_int;
  TCase *tc_core_from_decimal_to_float;
  TCase *tc_core_floor;
  TCase *tc_core_round;
  TCase *tc_core_truncate;
  TCase *tc_core_negate;*/

  s = suite_create("Decimal");
  /*tc_core_add = tcase_create("add_core");
  tc_core_sub = tcase_create("sub_core");
  tc_core_mul = tcase_create("mul_core");
  tc_core_div = tcase_create("div_core");*/
  tc_core_less = tcase_create("less_core");
  tc_core_less_or_equal = tcase_create("less_or_equal_core");
  tc_core_greater = tcase_create("greater_core");
  tc_core_greater_or_equal = tcase_create("greater_or_equal_core");
  tc_core_equal = tcase_create("equal_core");
  tc_core_not_equal = tcase_create("not_equal_core");
  /*tc_core_from_int_to_decimal = tcase_create("from_int_to_decimal_core");
  tc_core_from_float_to_decimal = tcase_create("from_float_to_decimal_core");
  tc_core_from_decimal_to_int = tcase_create("from_decimal_to_int_core");
  tc_core_from_decimal_to_float = tcase_create("from_decimal_to_float_core");
  tc_core_floor = tcase_create("floor_core");
  tc_core_round = tcase_create("round_core");
  tc_core_truncate = tcase_create("truncate_core");
  tc_core_negate = tcase_create("negate_core");*/
/*
  tcase_add_test(tc_core_add, test_add_1);
  suite_add_tcase(s, tc_core_add);

  tcase_add_test(tc_core_sub, test_sub_1);
  suite_add_tcase(s, tc_core_sub);

  tcase_add_test(tc_core_mul, test_mul_1);
  suite_add_tcase(s, tc_core_mul);

  tcase_add_test(tc_core_div, test_div_1);
  suite_add_tcase(s, tc_core_div);
*/
  // is_less()
  tcase_add_test(tc_core_less, test_less_1);
  tcase_add_test(tc_core_less, test_less_2);
  tcase_add_test(tc_core_less, test_less_3);
  tcase_add_test(tc_core_less, test_less_4);
  tcase_add_test(tc_core_less, test_less_5);
  tcase_add_test(tc_core_less, test_less_6);
  tcase_add_test(tc_core_less, test_less_7);
  tcase_add_test(tc_core_less, test_less_8);
  tcase_add_test(tc_core_less, test_less_9);
  tcase_add_test(tc_core_less, test_less_10);
  tcase_add_test(tc_core_less, test_less_11);
  tcase_add_test(tc_core_less, test_less_12);
  tcase_add_test(tc_core_less, test_less_13);
  tcase_add_test(tc_core_less, test_less_14);
  tcase_add_test(tc_core_less, test_less_15);
  tcase_add_test(tc_core_less, test_less_16);
  suite_add_tcase(s, tc_core_less);

  // is_less_or_equal()
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_1);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_2);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_3);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_4);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_5);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_6);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_7);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_8);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_9);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_10);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_11);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_12);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_13);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_14);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_15);
  tcase_add_test(tc_core_less_or_equal, test_less_or_equal_16);
  suite_add_tcase(s, tc_core_less_or_equal);

  // is_greater()
  tcase_add_test(tc_core_greater, test_greater_1);
  tcase_add_test(tc_core_greater, test_greater_2);
  tcase_add_test(tc_core_greater, test_greater_3);
  tcase_add_test(tc_core_greater, test_greater_4);
  tcase_add_test(tc_core_greater, test_greater_5);
  tcase_add_test(tc_core_greater, test_greater_6);
  tcase_add_test(tc_core_greater, test_greater_7);
  tcase_add_test(tc_core_greater, test_greater_8);
  tcase_add_test(tc_core_greater, test_greater_9);
  tcase_add_test(tc_core_greater, test_greater_10);
  tcase_add_test(tc_core_greater, test_greater_11);
  tcase_add_test(tc_core_greater, test_greater_12);
  tcase_add_test(tc_core_greater, test_greater_13);
  tcase_add_test(tc_core_greater, test_greater_14);
  tcase_add_test(tc_core_greater, test_greater_15);
  tcase_add_test(tc_core_greater, test_greater_16);
  suite_add_tcase(s, tc_core_greater);

  // is_greater_or_equal()
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_1);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_2);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_3);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_4);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_5);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_6);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_7);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_8);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_9);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_10);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_11);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_12);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_13);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_14);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_15);
  tcase_add_test(tc_core_greater_or_equal, test_greater_or_equal_16);
  suite_add_tcase(s, tc_core_greater_or_equal);

  // is_equal()
  tcase_add_test(tc_core_equal, test_equal_1);
  tcase_add_test(tc_core_equal, test_equal_2);
  tcase_add_test(tc_core_equal, test_equal_3);
  tcase_add_test(tc_core_equal, test_equal_4);
  tcase_add_test(tc_core_equal, test_equal_5);
  tcase_add_test(tc_core_equal, test_equal_6);
  tcase_add_test(tc_core_equal, test_equal_7);
  tcase_add_test(tc_core_equal, test_equal_8);
  tcase_add_test(tc_core_equal, test_equal_9);
  tcase_add_test(tc_core_equal, test_equal_10);
  tcase_add_test(tc_core_equal, test_equal_11);
  tcase_add_test(tc_core_equal, test_equal_12);
  tcase_add_test(tc_core_equal, test_equal_13);
  tcase_add_test(tc_core_equal, test_equal_14);
  tcase_add_test(tc_core_equal, test_equal_15);
  tcase_add_test(tc_core_equal, test_equal_16);
  suite_add_tcase(s, tc_core_equal);

  // is_not_equal()
  tcase_add_test(tc_core_not_equal, test_not_equal_1);
  tcase_add_test(tc_core_not_equal, test_not_equal_2);
  tcase_add_test(tc_core_not_equal, test_not_equal_3);
  tcase_add_test(tc_core_not_equal, test_not_equal_4);
  tcase_add_test(tc_core_not_equal, test_not_equal_5);
  tcase_add_test(tc_core_not_equal, test_not_equal_6);
  tcase_add_test(tc_core_not_equal, test_not_equal_7);
  tcase_add_test(tc_core_not_equal, test_not_equal_8);
  tcase_add_test(tc_core_not_equal, test_not_equal_9);
  tcase_add_test(tc_core_not_equal, test_not_equal_10);
  tcase_add_test(tc_core_not_equal, test_not_equal_11);
  tcase_add_test(tc_core_not_equal, test_not_equal_12);
  tcase_add_test(tc_core_not_equal, test_not_equal_13);
  tcase_add_test(tc_core_not_equal, test_not_equal_14);
  tcase_add_test(tc_core_not_equal, test_not_equal_15);
  tcase_add_test(tc_core_not_equal, test_not_equal_16);
  suite_add_tcase(s, tc_core_not_equal);
/*
  tcase_add_test(tc_core_from_int_to_decimal, test_from_int_to_decimal_1);
  suite_add_tcase(s, tc_core_from_int_to_decimal);

  tcase_add_test(tc_core_from_float_to_decimal, test_from_float_to_decimal_1);
  suite_add_tcase(s, tc_core_from_float_to_decimal);

  tcase_add_test(tc_core_from_decimal_to_int, test_from_decimal_to_int_1);
  suite_add_tcase(s, tc_core_from_decimal_to_int);

  tcase_add_test(tc_core_from_decimal_to_float, test_from_decimal_to_float_1);
  suite_add_tcase(s, tc_core_from_decimal_to_float);

  tcase_add_test(tc_core_floor, test_floor_1);
  suite_add_tcase(s, tc_core_floor);

  tcase_add_test(tc_core_round, test_round_1);
  suite_add_tcase(s, tc_core_round);

  tcase_add_test(tc_core_truncate, test_truncate_1);
  suite_add_tcase(s, tc_core_truncate);

  tcase_add_test(tc_core_negate, test_negate_1);
  suite_add_tcase(s, tc_core_negate);
*/
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = decimal_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE); //CK_NORMAL
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (!number_failed) ? EXIT_SUCCESS : EXIT_FAILURE;
}