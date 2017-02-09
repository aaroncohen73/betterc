CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic
SRCDIR = src
BINDIR = bin
IN = $(SRCDIR)/main.c $(SRCDIR)/lexer.c
OUT = $(BINDIR)/ce

all:
	mkdir -p $(BINDIR)
	$(CC) -o $(OUT) $(CFLAGS) $(CCFLAGS) $(IN)

clean:
	rm -f $(OUT)
