CC=gcc
CFLAGS=-I 

all:
	$(CC) -o uscrypt main.c decrypt.h encrypt.h

clean: 
	rm uscrypt