CC = gcc
SRCDIR = src
UTILDIR = util
IN = $(SRCDIR)/main.c $(SRCDIR)/lexer.c $(SRCDIR)/$(UTILDIR)/assert.c $(SRCDIR)/$(UTILDIR)/io.c $(SRCDIR)/$(UTILDIR)/linked_list.c
OUT = ce

all:
	$(CC) -o $(OUT) $(IN)
