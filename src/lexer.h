#ifndef LEXER_INCLUDE_H
#define LEXER_INCLUDE_H

#include <string.h>

#include "util/assert.h"
#include "util/io.h"

#define DEFAULT_MAX_LEX_LENGTH 20

typedef enum
{
    FLAG_NUMBER,
    FLAG_NAME,
    FLAG_OP, // (Binary) arithmetic, assignment, comparison
    FLAG_ENCLOSURE, // Parentheses, curly braces, square brackets and the like
    FLAG_SEPARATOR // Semicolons and commas
} flag_t;

struct token
{
    char *lexeme; // Null-terminated string
    unsigned int length;
    flag_t flag; // Flag indicating token type
    int operands; // Used for operator tokens. Unary (1) or binary (2)
    int orientation; // Used for enclosure tokens. -1 = left, 1 = right
    struct token *next;
};

typedef struct token token_t;

token_t * tokenize(char *line);

void delete_tokens(token_t *tokens);

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

token_t parse_number   (char *line, int pos, int *end_pos);
token_t parse_name     (char *line, int pos, int *end_pos);
token_t parse_operator (char *line, int pos, int *end_pos);
token_t parse_enclosure(char *line, int pos);
token_t parse_separator(char *line, int pos);

#endif
