#include <stdio.h>

#include "lexer.h"

void print_tokens(struct token *tokens)
{
    printf("Type: %u, Lexeme: %s\n", tokens->flag, tokens->lexeme);

    if (tokens->next != NULL)
    {
        print_tokens(tokens->next);
    }
}


int main()
{
    struct token *tokens;
    char user_input[80];

    printf("> Type a mathematical expression: ");
    fgets(user_input, 79, stdin);

    tokens = tokenize(user_input);

    print_tokens(tokens);

    delete_tokens(tokens);

    return 0;
}
