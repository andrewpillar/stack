CC=cc
CFLAGS=-Wall -Werror -Wpedantic -std=c11

.PHONY: stack

stack: stack.c
	$(CC) $(CFLAGS) -o $@.out $<
