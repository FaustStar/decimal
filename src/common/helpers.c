#include "../s21_decimal.h"

// --------------------------------------- НОРМАЛИЗАЦИЯ ---------------------------------------

void normalize(s21_big_decimal *value_1, s21_big_decimal *value_2) {
    int exp_1 = get_big_exp(*value_1);
    int exp_2 = get_big_exp(*value_2);
    if (exp_1 != exp_2) {
        if (exp_1 < exp_2) {
            for (int i = 1; exp_1 + i <= exp_2; i++) {
                scale_up(value_1, 1);
            }
        } else {
            normalize(value_2, value_1);
        }
    }
}

// multiplication by 10
void scale_up(s21_big_decimal *value, int num) {
    int new_exp = get_big_exp(*value) + num;
    if (new_exp <= 28) {
        set_big_exp(value, new_exp);
        s21_big_decimal temp_1 = *value, temp_2 = *value;
        big_left_shift(&temp_1, 3);
        big_left_shift(&temp_2, 1);
        bit_addition(temp_1, temp_2, value);
    }
}

// addition bit by bit
void bit_addition(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
    int storage = 0;
    for (int i = 0; i < 224; i++) {
        int add_result = get_big_bit(value_1, i) + get_big_bit(value_2, i) + storage;
        storage = add_result / 2;
        set_big_bit(result, i, add_result % 2);
    }
}

// --------------------------------------- Перевод из DECIMAL в BIG DECIMAL и обратно ---------------------------------------

s21_big_decimal decimal_to_big_decimal(s21_decimal decimal) {
    s21_big_decimal new_decimal = {0};
    new_decimal.bits[0] = decimal.bits[0];
    new_decimal.bits[1] = decimal.bits[1];
    new_decimal.bits[2] = decimal.bits[2];
    new_decimal.bits[7] = decimal.bits[3];
    return new_decimal;
    
}

s21_decimal big_decimal_to_decimal(s21_big_decimal big) {
    s21_decimal new_decimal = {0};
    new_decimal.bits[0] = big.bits[0];
    new_decimal.bits[1] = big.bits[1];
    new_decimal.bits[2] = big.bits[2];
    new_decimal.bits[3] = big.bits[7];
    return new_decimal;
}