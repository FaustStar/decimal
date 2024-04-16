#include "../s21_decimal.h"

int compare(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);
    if (sign_1 != sign_2) {
        res = sign_1 ? LESS : GREATER;
    } else {
        s21_big_decimal big_value_1 = decimal_to_big_decimal(value_1);
        s21_big_decimal big_value_2 = decimal_to_big_decimal(value_2);
        normalize(&big_value_1, &big_value_2);
        if (!sign_1) {
            //comparison of positive numbers
            res = compare_mantissa(big_value_1, big_value_2);
        } else {
            //comparison of negative numbers
            res = compare_mantissa(big_value_1, big_value_2);
            if (res != EQUAL) {
                res = (res == GREATER) ? LESS : GREATER;
            }
        }
    }
    return res;
}

//comparison of mantissas bit by bit
int compare_mantissa(s21_big_decimal value_1, s21_big_decimal value_2) {
    int res = 0;
    int stop = 0;
    for (int i = 223; i >= 0 && !stop; i--) {
        int bit_1 = get_big_bit(value_1, i);
        int bit_2 = get_big_bit(value_2, i);
        if (bit_1 != bit_2) {
            stop = 1;
            res = bit_1 ? GREATER : LESS;
        } else {
            res = EQUAL;
        }
    }
    return res;
}