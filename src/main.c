#include <stdio.h>

#include "lexer.h"

int main()
{
    list_t tokens;
    list_node_t *a;
    token_t *token;
    char user_input[80];
    int i;

    fgets(user_input, 79, stdin);

    tokens = tokenize(user_input);
    emit("%d", tokens.length);

    for (i = 0; i < tokens.length; i++)
    {
        a = list_at(&tokens, i);
        token = (token_t *) a->data;
        emit("Type: %d, Lexeme: %s", token->flag, token->lexeme);
    }

    list_delete(&tokens);

    return 0;
}
