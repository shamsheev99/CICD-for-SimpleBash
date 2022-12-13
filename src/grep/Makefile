.PHONY: all s21_grep clean rebuild
CC2=gcc
LDFLAGS=
LIBFLAGS=-lpcre

default: all

all:	s21_grep 

s21_grep:
	$(CC2) $(LDFLAGS) s21_grep.c -o s21_grep $(LIBFLAGS)

clean:
	rm -rf s21_grep
	clear

rebuild: clean all
