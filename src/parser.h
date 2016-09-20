#ifndef PARSER_INCLUDE_H
#define PARSER_INCLUDE_H

#include "lexer.h"

typedef struct
{
    // Just signed long ints for now
    long num;
} num_t;

typedef struct
{
    char *name;
    unsigned int length;
} ident_t;

typedef enum
{
    ADDOP_ADD,
    ADDOP_SUB,
    ADDOP_NONE,
} addop_t;

typedef enum
{
    MULOP_MUL,
    MULOP_DIV,
    MULOP_NONE
} mulop_t;

// Forward decl. for factor_union_t
typedef struct expr expr_t;

typedef union
{
    expr_t *expr;
    ident_t *ident;
    num_t *num;
} factor_union_t;

typedef enum
{
    FACTOR_EXPRESSION,
    FACTOR_IDENTIFY,
    FACTOR_NUM
} factor_enum_t;

typedef struct
{
    factor_union_t data;
    factor_enum_t type;
} factor_t;

struct term
{
    factor_t *factor;
    mulop_t mulop;
    struct term *next;
};

typedef struct term term_t;

struct expr
{
    term_t *term;
    addop_t addop;
    struct expr *next;
};

//typedef struct expr expr_t;

addop_t parse_addop(token_t **tokens);
mulop_t parse_mulop(token_t **tokens);

num_t * parse_num(token_t **tokens);
ident_t * parse_ident(token_t **tokens);
factor_t * parse_factor(token_t **tokens);
term_t * parse_term(token_t **tokens);
expr_t * parse_expr(token_t **tokens);

void delete_num(num_t *num);
void delete_ident(ident_t *ident);
void delete_factor(factor_t *factor);
void delete_term(term_t *term);
void delete_expr(expr_t *expr);

#endif
