#ifndef PARSER_INCLUDE_H
#define PARSER_INCLUDE_H

#include "lexer.h"

struct ast_atom
{
    double num;
};

enum ast_type
{
    AST_TYPE_LITERAL,
    AST_TYPE_OPERATOR_ADD,
    AST_TYPE_OPERATOR_SUBTRACT,
    AST_TYPE_OPERATOR_MULTIPLY,
    AST_TYPE_OPERATOR_DIVIDE,
};

struct ast_node
{
    enum ast_type type;

    struct ast_atom *atom;
    struct ast_node *next_sib;
    struct ast_node *first_child;
};

struct ast_node * create_ast_node(void);

struct ast_node * parse_tokens(struct token *);

#endif
