# decimal

My study project: development of my own s21_decimal.h library using C programming language. The library adds the ability to work with the "decimal" type, which is not in the language standard.

## Content

1. [Binary representation](#binary-representation)
2. [Functions](#functions) \
    2.1. [Comparison Operators](#comparison-operators)

## Binary representation

The binary representation of a Decimal number consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the integer number and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28.

Decimal number was implemented as a four-element array of 32-bit unsigned integers (unsigned int bits[4];).

```bits[0]```, ```bits[1]```, and ```bits[2]``` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.
```bits[3]``` contains the scale factor and sign, and consists of following parts:

* Bits 0 to 15, the lower word, are unused and must be zero.
* Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
* Bits 24 to 30 are unused and must be zero.
* Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

## Functions

### Comparison Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | int s21_is_less(s21_decimal, s21_decimal) |
| Less than or equal to | <= | int s21_is_less_or_equal(s21_decimal, s21_decimal) | 
| Greater than | > |  int s21_is_greater(s21_decimal, s21_decimal) |
| Greater than or equal to | >= | int s21_is_greater_or_equal(s21_decimal, s21_decimal) | 
| Equal to | == |  int s21_is_equal(s21_decimal, s21_decimal) |
| Not equal to | != |  int s21_is_not_equal(s21_decimal, s21_decimal) |

Return value:
* 0 - FALSE
* 1 - TRUE