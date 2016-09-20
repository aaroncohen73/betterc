CC = gcc
CFLAGS = -std=gnu99
CCFLAGS = -Wall -Wextra -Wpedantic
SRCDIR = src
BINDIR = bin
IN = $(SRCDIR)/main.c $(SRCDIR)/lexer.c $(SRCDIR)/parser.c
OUT = $(BINDIR)/ce

all:
	$(CC) -o $(OUT) $(CFLAGS) $(CCFLAGS) $(IN) $(UTIL_IN)
