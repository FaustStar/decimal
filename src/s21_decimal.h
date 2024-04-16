#ifndef S21__DECIMAL__
#define S21__DECIMAL__

#define OK 0
#define CLOSE_TO_INFINITY 1
#define CLOSE_TO_MINUS_INFINITY 2
#define DIVISION_BY_ZERO 3
#define FALSE 0
#define TRUE 1
#define CONVERSION_ERROR 1
#define CALCULATION_ERROR 1
#define GREATER 1
#define LESS -1
#define EQUAL 0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Common functions (used for implementation of the functions from the task)
int get_bit(s21_decimal value, int index);
void set_bit(s21_decimal *value, int index, int bit);
void set(s21_decimal *value, int bit, int index_32, int rank, int index_96);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_exp(s21_decimal value);
void set_exp(s21_decimal *value, int exp);
void left_shift(s21_decimal *value, int shift);
void right_shift(s21_decimal *value, int shift);
void normalize(s21_big_decimal *value_1, s21_big_decimal *value_2);
void scale_up(s21_big_decimal *value, int num);
void bit_addition(s21_big_decimal value_1, s21_big_decimal value_2,
                  s21_big_decimal *result);
int get_big_bit(s21_big_decimal value, int index);
void set_big_bit(s21_big_decimal *value, int index, int bit);
void set_big(s21_big_decimal *value, int bit, int index_32, int rank,
             int index_96);
int get_big_sign(s21_big_decimal value);
void set_big_sign(s21_big_decimal *value, int sign);
int get_big_exp(s21_big_decimal value);
void set_big_exp(s21_big_decimal *value, int exp);
void big_left_shift(s21_big_decimal *value, int shift);
void big_right_shift(s21_big_decimal *value, int shift);
s21_big_decimal decimal_to_big_decimal(s21_decimal decimal);
s21_decimal big_decimal_to_decimal(s21_big_decimal big);
int compare(s21_decimal value_1, s21_decimal value_2);
int compare_mantissa(s21_big_decimal value_1, s21_big_decimal value_2);

#endif