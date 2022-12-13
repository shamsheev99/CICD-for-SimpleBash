.PHONY: all test test_cat test_grep s21_cat s21_cat.o s21_grep s21_grep.o clean rebuild check
CC=gcc
CC2=gcc
CFLAGS=-c
LIBFLAGS=-lpcre
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC2 += -D OS_MAC
else
	CC2 += -D OS_LINUX
endif

default: all

all:	s21_cat s21_grep 
test: test_cat test_grep

test_cat: s21_cat
	chmod +x test/test_c.sh
	test/test_c.sh
test_grep: s21_grep
	chmod +x test/test_g.sh
	test/test_g.sh

s21_cat: cat/s21_cat.c 
	$(CC) $(LDFLAGS) -o s21_cat cat/s21_cat.c
	cp s21_cat cat/s21_cat 

s21_grep: grep/s21_grep.c 
	$(CC) $(LDFLAGS) -o s21_grep grep/s21_grep.c -lpcre
	cp s21_grep grep/s21_grep

clean:
	rm -rf test*.txt cat/*.o grep/*.o cat/s21_cat grep/s21_grep test_gen test_cmp 
	rm -rf test/test_grep.* test/test_cat.*  test/test_s21_grep.* test/test_s21_cat.*
	rm -rf test/test_cmp test/test_gen test/test_gen_grep 
	rm -rf a.out cat/a.out grep/a.out test/a.out
	clear

rebuild: clean all

check:
	python3 ./cpplint.py --extension=c cat/*.c grep/*.c
	#CK_FORK=no leaks --atExit -- ./test
