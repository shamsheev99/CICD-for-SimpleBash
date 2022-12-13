.PHONY: all s21_cat clean rebuild
CC2=gcc
LDFLAGS=
LIBFLAGS=-lpcre

default: all

all:	s21_cat

s21_cat:
	$(CC2) $(LDFLAGS) s21_cat.c -o s21_cat $(LIBFLAGS)

clean:
	rm -rf s21_cat 
	clear

rebuild: clean all
