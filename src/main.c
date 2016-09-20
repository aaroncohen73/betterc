#include <stdio.h>

#include "lexer.h"
#include "parser.h"

void print_tokens(token_t *tokens)
{
    printf("Type: %d, Lexeme: %s\n", tokens->flag, tokens->lexeme);

    if (tokens->next != NULL)
    {
        print_tokens(tokens->next);
    }
}

void print_expr(expr_t *expr);

void print_term(term_t *term)
{
    printf("Start Term\n");

    printf("Start Factor\n");

    switch (term->factor->type)
    {
        case FACTOR_EXPRESSION:
            print_expr(term->factor->data.expr);
            break;
        case FACTOR_IDENTIFY:
            printf("%s\n", term->factor->data.ident->name);
            break;
        case FACTOR_NUM:
            printf("%d\n", term->factor->data.num->num);
            break;
    }

    printf("End factor\n");

    switch (term->mulop)
    {
        case MULOP_MUL:
            printf("*\n");
            break;
        case MULOP_DIV:
            printf("/\n");
            break;
        default:
            printf("End term\n");
            break;
    }

    if (term->next != NULL)
    {
        print_term(term->next);
    }
}

void print_expr(expr_t *expr)
{
    printf("Start Expr\n");
    print_term(expr->term);

    switch (expr->addop)
    {
        case ADDOP_ADD:
            printf("+\n");
            break;
        case ADDOP_SUB:
            printf("-\n");
            break;
        default:
            printf("End expr\n");
            break;
    }

    if (expr->next != NULL)
    {
        print_expr(expr->next);
    }
}

int main()
{
    token_t *tokens, *tokens_cpy;
    expr_t *expr;
    char user_input[80];

    fgets(user_input, 79, stdin);

    tokens = tokenize(user_input);

    print_tokens(tokens);

    tokens_cpy = tokens;

    expr = parse_expr(&tokens_cpy);

    print_expr(expr);

    delete_tokens(tokens);

    delete_expr(expr);

    return 0;
}
