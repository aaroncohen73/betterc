CC = gcc
CFLAGS = -std=gnu99
CCFLAGS = -Wall -Wextra -Wpedantic
SRCDIR = src
BINDIR = bin
UTILDIR = $(SRCDIR)/util
UTIL_IN = $(UTILDIR)/assert.c $(UTILDIR)/io.c
UTIL_OUT = $(BINDIR)/util.a
IN = $(SRCDIR)/main.c $(SRCDIR)/lexer.c $(SRCDIR)/parser.c
OUT = $(BINDIR)/ce

all:
	$(CC) -o $(OUT) $(CFLAGS) $(CCFLAGS) $(IN) $(UTIL_IN)

util:
	$(CC) -o $(UTIL_OUT) $(CFLAGS) $(CCFLAGS) $(UTIL_IN)
