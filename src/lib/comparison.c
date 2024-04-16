#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) == LESS) ? TRUE : FALSE;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) != GREATER) ? TRUE : FALSE;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) == GREATER) ? TRUE : FALSE;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) != LESS) ? TRUE : FALSE;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) == EQUAL) ? TRUE : FALSE;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    return (compare(value_1, value_2) != EQUAL) ? TRUE : FALSE;
}