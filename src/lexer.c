#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

token_t * tokenize(char *line)
{
    token_t *token_base = NULL, *token_current, token_next;
    int line_len, pos;

    line_len = strlen(line);

    for (pos = 0; pos < line_len; pos++)
    {
        if (IS_WHITE(line[pos]))
        {
            continue;
        }
        else if (IS_NUMBER(line[pos]))
        {
            token_next = parse_number(line, pos, &pos);
        }
        else if (IS_ALPHA(line[pos]))
        {
            token_next = parse_name(line, pos, &pos);
        }
        else if (IS_OPERATOR(line[pos]))
        {
            token_next = parse_operator(line, pos, &pos); 
        }
        else if (IS_ENCLOSURE(line[pos]))
        {
            token_next = parse_enclosure(line, pos);
        }
        else if (IS_SEPARATOR(line[pos]))
        {
            token_next = parse_separator(line, pos);
        }
        else
        {
            printf("Error: Count not parse line at position %d\n", pos);
            printf("Character: %c\n", line[pos]);
            printf("%s\n", line);
            break;
        }

        if (token_base == NULL)
        {
            token_base = malloc(sizeof(token_t));
            *token_base = token_next;
            token_current = token_base;
        }
        else
        {
            token_current->next = malloc(sizeof(token_t));
            memcpy(token_current->next, &token_next, sizeof(token_t));
            token_current = token_current->next;
        }
    }

    return token_base;
}

void delete_tokens(token_t *tokens)
{
    token_t *next = tokens->next;

    free(tokens->lexeme);
    free(tokens);

    if (next != NULL)
    {
        delete_tokens(next);
    }
}

token_t parse_number(char *line, int pos, int *end_pos)
{
    token_t token;
    char *raw_number;
    int length = 0, position = pos;
    int decimal = 0;

    raw_number = malloc(DEFAULT_MAX_LEX_LENGTH);

    while (IS_NUMBER(line[position]) || 
            (line[position] == '.' && !decimal))
    {
        if (line[position] == '.')
            decimal = 1;

        raw_number[length++] = line[position++];
    }

    raw_number[length] = '\0';

    *end_pos = position - 1;

    token.lexeme = raw_number;
    token.length = length - 1; 
    token.flag = FLAG_NUMBER;
    token.next = NULL;

    return token;
}

token_t parse_name(char *line, int pos, int *end_pos)
{
    token_t token;
    char *raw_name;
    int length = 0, position = pos;

    raw_name = malloc(DEFAULT_MAX_LEX_LENGTH);

    while (IS_ALPHA(line[position]) ||
            (IS_NUMBER(line[position]) && length > 0))
    {
        raw_name[length++] = line[position++];
    }

    raw_name[length] = '\0';

    *end_pos = position - 1;

    token.lexeme = raw_name;
    token.length = length;
    token.flag = FLAG_NAME;
    token.next = NULL;

    return token;
}

token_t parse_operator(char *line, int pos, int *end_pos)
{
    token_t token;
    char *raw_op;
    int length = 0, position = pos;

    raw_op = malloc(DEFAULT_MAX_LEX_LENGTH);

    while (IS_OPERATOR(line[position]))
    {
        raw_op[length++] = line[position++];
    }

    raw_op[length] = '\0';

    *end_pos = position - 1;

    token.lexeme = raw_op;
    token.length = length - 1;
    token.flag = FLAG_OP;
    token.next = NULL;
    // TODO: figure out good way to detect operands
    return token;
}
token_t parse_enclosure(char *line, int pos)
{
    token_t token;
    char *raw_enc;

    raw_enc = malloc(2);
    raw_enc[0] = line[pos];
    raw_enc[1] = '\0';

    token.lexeme = raw_enc;
    token.length = 1;
    token.flag = FLAG_ENCLOSURE;
    token.next = NULL;

    if (line[pos] == '(' ||
            line[pos] == '[' ||
            line[pos] == '{')
    {
        token.orientation = -1;
    }
    else
    {
        token.orientation = 1;
    }

    return token;
}
token_t parse_separator(char *line, int pos)
{
    token_t token;
    char *raw_sep;

    raw_sep = malloc(2);
    raw_sep[0] = line[pos];
    raw_sep[1] = '\0';

    token.lexeme = raw_sep;
    token.length = 1;
    token.flag = FLAG_SEPARATOR;
    token.next = NULL;

    return token;
}
