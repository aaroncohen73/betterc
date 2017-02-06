#ifndef LEXER_INCLUDE_H
#define LEXER_INCLUDE_H

#include <stdlib.h>
#include <string.h>

#define DEFAULT_MAX_LEX_LENGTH 20

enum token_flag
{
    TOKEN_FLAG_NUMBER,
    TOKEN_FLAG_NAME,
    TOKEN_FLAG_OP, // (Binary) arithmetic, assignment, comparison
    TOKEN_FLAG_ENCLOSURE, // Parentheses, curly braces, square brackets, etc.
    TOKEN_FLAG_SEPARATOR // Semicolons and commas
};

struct token
{
    char *lexeme; // Null-terminated string
    size_t length;
    enum token_flag flag; // Flag indicating token type
    int operands; // Used for operator tokens. Unary (1) or binary (2)
    int orientation; // Used for enclosure tokens. -1 = left, 1 = right
    struct token *next;
};

struct token * tokenize(char *);

void delete_tokens(struct token *);

#define IS_WHITE(c) (c == 0x09 || \
                     c == 0x20 || \
                     c == 0x0A || \
                     c == 0x0D)

#define IS_NUMBER(c) (c >= '0' && c <= '9')

#define IS_ALPHA(c) (c >= 'A' && c <= 'Z') || \
                    (c >= 'a' && c <= 'z')

#define IS_OPERATOR(c) (c == 0x21 || \
                        c == 0x25 || \
                        c == 0x26 || \
                        c == 0x2A || \
                        c == 0x2B || \
                        c == 0x2D || \
                        c == 0x2F || \
                       (c >= 0x3C && c <= 0x3E) || \
                        c == 0x5E || \
                        c == 0x7C || \
                        c == 0x7E)

#define IS_ENCLOSURE(c) ((c == '(' || c == ')') || \
                         (c == '[' || c == ']') || \
                         (c == '{' || c == '}'))

#define IS_SEPARATOR(c) (c == ',' || \
                         c == ';')

size_t parse_number   (struct token *, char *, size_t);
size_t parse_name     (struct token *, char *, size_t);
size_t parse_operator (struct token *, char *, size_t);
size_t parse_enclosure(struct token *, char *, size_t);
size_t parse_separator(struct token *, char *, size_t);

#endif
