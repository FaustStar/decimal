#include "../s21_decimal.h"

// --------------------------------------- МАНТИССА
// ---------------------------------------

// для DECIMAL

// index - [0; 95]
int get_bit(s21_decimal value, int index) {
  int res = 0;
  if (index >= 0 && index <= 31) {
    res = (value.bits[0] & (1 << index)) >> index;
  } else if (index >= 32 && index <= 63) {
    res = (value.bits[1] & (1 << (index - 32))) >> (index - 32);
  } else if (index >= 64 && index <= 95) {
    res = (value.bits[2] & (1 << (index - 64))) >> (index - 64);
  }
  return res;
}

// index - [0; 95], bit - 0 or 1
void set_bit(s21_decimal *value, int index, int bit) {
  if (index >= 0 && index <= 31) {
    set(value, bit, index, 0, index);
  } else if (index >= 32 && index <= 63) {
    set(value, bit, index - 32, 1, index);
  } else if (index >= 64 && index <= 95) {
    set(value, bit, index - 64, 2, index);
  }
}

void set(s21_decimal *value, int bit, int index_32, int rank, int index_96) {
  int cur_bit = get_bit(*value, index_96);
  if (cur_bit && !bit) {
    value->bits[rank] &= ~(1 << index_32);  // set 0 instead of 1
  } else if (!cur_bit && bit) {
    value->bits[rank] |= (1 << index_32);  // set 1 instead of 0
  }
}

// для BIG DECIMAL

// index - [0; 255] (you can also get bits from bits[7] where a sign and an exp
// are)
int get_big_bit(s21_big_decimal value, int index) {
  int res = 0;

  int first_bit_num = 0;
  for (int i = 0; i < 8; i++) {
    if (index >= first_bit_num && index <= (first_bit_num + 31)) {
      res = (value.bits[i] & (1 << (index - first_bit_num))) >>
            (index - first_bit_num);
    }
    first_bit_num += 32;
  }

  return res;
}

void set_big_bit(s21_big_decimal *value, int index, int bit) {
  int first_bit_num = 0;
  for (int i = 0; i < 8; i++) {
    if (index >= first_bit_num && index <= (first_bit_num + 31)) {
      set_big(value, bit, index - first_bit_num, i, index);
    }
    first_bit_num += 32;
  }
}

void set_big(s21_big_decimal *value, int bit, int index_32, int rank,
             int index_96) {
  int cur_bit = get_big_bit(*value, index_96);
  if (cur_bit && !bit) {
    value->bits[rank] &= ~(1 << index_32);  // set 0 instead of 1
  } else if (!cur_bit && bit) {
    value->bits[rank] |= (1 << index_32);  // set 1 instead of 0
  }
}

// --------------------------------------- ЗНАК
// ---------------------------------------

// для DECIMAL

int get_sign(s21_decimal value) { return (value.bits[3] & (1 << 31)) >> 31; }

void set_sign(s21_decimal *value, int sign) {
  int cur_sign = get_sign(*value);
  if (cur_sign && !sign) {
    value->bits[3] &= ~(1 << 31);  // set 0 instead of 1
  } else if (!cur_sign && sign) {
    value->bits[3] |= (1 << 31);  // set 1 instead of 0
  }
}

// для BIG DECIMAL

int get_big_sign(s21_big_decimal value) {
  return (value.bits[7] & (1 << 31)) >> 31;
}

void set_big_sign(s21_big_decimal *value, int sign) {
  int cur_sign = get_big_sign(*value);
  if (cur_sign && !sign) {
    value->bits[7] &= ~(1 << 31);  // set 0 instead of 1
  } else if (!cur_sign && sign) {
    value->bits[7] |= (1 << 31);  // set 1 instead of 0
  }
}

// --------------------------------------- СТЕПЕНЬ
// ---------------------------------------

// для DECIMAL

int get_exp(s21_decimal value) {
  set_sign(&value, 0);
  return value.bits[3] >> 16;
}

void set_exp(s21_decimal *value, int exp) {
  int sign = get_sign(*value);
  value->bits[3] <<= 16;
  for (int i = 0; i < 8; i++) {
    int bit = (exp & (1 << i)) >> i;  // get bit from exponent
    if (bit) {
      value->bits[3] |= (1 << i);  // set 1 instead of 0
    }
  }
  value->bits[3] <<= 16;
  set_sign(value, sign);
}

// для BIG DECIMAL

int get_big_exp(s21_big_decimal value) {
  set_big_sign(&value, 0);
  return value.bits[7] >> 16;
}

void set_big_exp(s21_big_decimal *value, int exp) {
  int sign = get_big_sign(*value);
  value->bits[7] <<= 16;
  for (int i = 0; i < 8; i++) {
    int bit = (exp & (1 << i)) >> i;  // get bit from exponent
    if (bit) {
      value->bits[7] |= (1 << i);  // set 1 instead of 0
    }
  }
  value->bits[7] <<= 16;
  set_big_sign(value, sign);
}

// --------------------------------------- СДВИГИ БЕЗ ПОТЕРИ ТОЧНОСТИ
// ---------------------------------------

// для DECIMAL

void left_shift(s21_decimal *value, int shift) {
  unsigned int storage = 0;
  for (int i = 0; i <= 2; i++) {
    unsigned int copy = value->bits[i];
    value->bits[i] <<= shift;
    value->bits[i] |= storage;
    storage = copy >> (32 - shift);
  }
}

void right_shift(s21_decimal *value, int shift) {
  unsigned int storage = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned int copy = value->bits[i];
    value->bits[i] >>= shift;
    value->bits[i] |= storage;
    storage = copy << (32 - shift);
  }
}

// для BIG DECIMAL

void big_left_shift(s21_big_decimal *value, int shift) {
  unsigned int storage = 0;
  for (int i = 0; i <= 6; i++) {
    unsigned int copy = value->bits[i];
    value->bits[i] <<= shift;
    value->bits[i] |= storage;
    storage = copy >> (32 - shift);
  }
}

void big_right_shift(s21_big_decimal *value, int shift) {
  unsigned int storage = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned int copy = value->bits[i];
    value->bits[i] >>= shift;
    value->bits[i] |= storage;
    storage = copy << (32 - shift);
  }
}