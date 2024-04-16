CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

LIB = ./lib/*.c
COMMON = ./common/*.c
OBJECTS = *.o
TEST = decimal_test.c

CLANG_PATH = ../materials/linters/
CLANG_COPY = cp $(CLANG_PATH).clang-format .clang-format

OS = $(shell uname)

ifeq ($(OS), Darwin)
 	TEST_FLAGS = -lcheck
	OPEN_CMD = open
else
 	TEST_FLAGS = -lcheck -lsubunit -lrt -lpthread -lm
	OPEN_CMD = xdg-open
endif

.PHONY: all clean rebuild

all: s21_decimal.a test gcov_report

clean:
	rm -rf $(OBJECTS) *.a *.gch *.gcda *.gcno *.info report test .clang-format

test: s21_decimal.a
	$(CC) $(CFLAGS) $(LIB) $(COMMON) $(TEST) ./s21_decimal.a $(TEST_FLAGS) -o test
	./test

s21_decimal.a: s21_decimal.o
	ar r s21_decimal.a $(OBJECTS)

s21_decimal.o:
	$(CC) $(CFLAGS) ./s21_decimal.h $(LIB) $(COMMON) -c

gcov_report: s21_decimal.a
	$(CC) $(CFLAGS) --coverage $(TEST) $(LIB) $(COMMON) -L. s21_decimal.a $(TEST_FLAGS) -o test
	./test
	lcov -t "test" -o tests.info -c -d .
	genhtml -o report tests.info
	$(OPEN_CMD) ./report/index.html

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

rebuild:
	$(MAKE) clean
	$(MAKE) all

clang:
	$(CLANG_COPY) && clang-format -n $(LIB) $(COMMON) *.c *.h
	$(CLANG_COPY) && clang-format -i $(LIB) $(COMMON) *.c *.h

verter:
	cd ../materials/build && sh run.sh
	cd ../../