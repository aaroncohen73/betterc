#include <stdio.h>

#include "lexer.h"
#include "parser.h"

void print_tokens(token_t *tokens)
{
    emit("Type: %d, Lexeme: %s", tokens->flag, tokens->lexeme);

    if (tokens->next != NULL)
    {
        print_tokens(tokens->next);
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

    delete_tokens(tokens);

    delete_expr(expr);

    return 0;
}
