CC = gcc
CFLAGS = -Wall -ggdb

DOP: main.c RBT.c
	$(CC) $(CFLAGS) -o a.out -std="c99" main.c RBT.c
