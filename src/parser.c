#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "util/io.h"

addop_t parse_addop(token_t **tokens)
{
    addop_t addop = ADDOP_NONE;

    if (*tokens == NULL)
    {
        return addop;
    }

    if (strncmp((**tokens).lexeme, "+", 1) == 0)
    {
        addop = ADDOP_ADD;
    }
    else if (strncmp((**tokens).lexeme, "-", 1) == 0)
    {
        addop = ADDOP_SUB;
    }

    if (addop != ADDOP_NONE)
    {
        // Next token
        *tokens = (**tokens).next;
    }

    return addop;
}

mulop_t parse_mulop(token_t **tokens)
{
    mulop_t mulop = MULOP_NONE;

    if (*tokens == NULL)
    {
        return mulop;
    }

    if (strncmp((**tokens).lexeme, "*", 1) == 0)
    {
        mulop = MULOP_MUL;
    }
    else if (strncmp((**tokens).lexeme, "/", 1) == 0)
    {
        mulop = MULOP_DIV;
    }

    if (mulop != MULOP_NONE)
    {
        // Next token
        *tokens = (**tokens).next;
    }

    return mulop;
}

ident_t * parse_ident(token_t **tokens)
{
    ident_t *ident = NULL;

    if (*tokens == NULL)
    {
        return ident;
    }

    ident = malloc(sizeof(ident_t));

    ident->name = malloc((**tokens).length + 1);
    ident->length = (**tokens).length;

    strncpy((**tokens).lexeme, ident->name, ident->length);
    ident->name[ident->length + 1] = '\0';

    // Next token
    *tokens = (**tokens).next;

    return ident;
}

num_t * parse_num(token_t **tokens)
{
    num_t *num = NULL;

    if (*tokens == NULL)
    {
        return num;
    }

    num = malloc(sizeof(num_t));

    num->num = atol((**tokens).lexeme);

    // Next token
    *tokens = (**tokens).next;

    return num;
}

factor_t * parse_factor(token_t **tokens)
{
    factor_t *factor = NULL;

    if (*tokens == NULL)
    {
        return factor;
    }

    factor = malloc(sizeof(factor_t));

    // If the factor is an expression enclosed in parenthesis (will make correct later)
    if ((**tokens).flag == FLAG_ENCLOSURE && (**tokens).orientation == -1)
    {
        // Next token
        *tokens = (**tokens).next;

        factor->type = FACTOR_EXPRESSION;
        factor->data.expr = parse_expr(tokens);

        // Match closing parenthesis
        if ((**tokens).flag != FLAG_ENCLOSURE || (**tokens).orientation != 1)
        {
            // Unable to match closing parenthesis
            delete_factor(factor);
            return NULL;
        }

        // Next token
        *tokens = (**tokens).next;
    } // If the factor is a number
    else if ((**tokens).flag == FLAG_NUMBER)
    {
        factor->type = FACTOR_NUM;
        factor->data.num = parse_num(tokens);
    } // If the factor is an identifier
    else if ((**tokens).flag == FLAG_NAME)
    {
        factor->type = FACTOR_IDENTIFY;
        factor->data.ident = parse_ident(tokens);
    }

    return factor;
}

term_t * parse_term(token_t **tokens)
{
    term_t *term = NULL;

    if (*tokens == NULL)
    {
        return term;
    }

    term = malloc(sizeof(term_t));
    term->next = NULL;

    term->factor = parse_factor(tokens);
    term->mulop = parse_mulop(tokens);

    if (term->mulop != MULOP_NONE)
    {
        term->next = parse_term(tokens);
    }

    return term;
}

expr_t * parse_expr(token_t **tokens)
{
    expr_t *expr = NULL;

    if (*tokens == NULL)
    {
        return expr;
    }

    expr = malloc(sizeof(expr_t));
    expr->next = NULL;

    expr->term = parse_term(tokens);
    expr->addop = parse_addop(tokens);

    if (expr->addop != ADDOP_NONE)
    {
        expr->next = parse_expr(tokens);
    }

    return expr;
}

void delete_num(num_t *num)
{
    if (num == NULL)
    {
        return;
    }

    free(num);
}

void delete_ident(ident_t *ident)
{
    if (ident == NULL)
    {
        return;
    }

    free(ident->name);
    free(ident);
}

void delete_factor(factor_t *factor)
{
    if (factor == NULL)
    {
        return;
    }

    if (factor->type == FACTOR_EXPRESSION)
    {
        delete_expr(factor->data.expr);
    }
    else if (factor->type == FACTOR_IDENTIFY)
    {
        delete_ident(factor->data.ident);
    }
    else if (factor->type == FACTOR_NUM)
    {
        delete_num(factor->data.num);
    }

    free(factor);
}

void delete_term(term_t *term)
{
    if (term == NULL)
    {
        return;
    }

    delete_factor(term->factor);
    delete_term(term->next);

    free(term);
}

void delete_expr(expr_t *expr)
{
    if (expr == NULL)
    {
        return;
    }

    delete_term(expr->term);
    delete_expr(expr->next);

    free(expr);
}
