CC = gcc
CFLAGS = -std=gnu99
CCFLAGS = -Wall -Wextra -pedantic
SRCDIR = src
BINDIR = bin
IN = $(SRCDIR)/main.c $(SRCDIR)/lexer.c
OUT = $(BINDIR)/ce

all:
	mkdir -p $(BINDIR)
	$(CC) -o $(OUT) $(CFLAGS) $(CCFLAGS) $(IN) $(UTIL_IN)
