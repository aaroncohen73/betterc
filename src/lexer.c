#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"


struct token * tokenize(char *line)
{
    struct token *base = NULL, *cur, *next, t;
    size_t pos_offset;

    for (size_t pos = 0; pos < strlen(line); pos++)
    {
        if (IS_WHITE(line[pos]))
        {
            continue;
        }
        else if (IS_NUMBER(line[pos]))
        {
            pos_offset = parse_number(&t, line, pos);

            if (pos_offset == 0)
                goto tokenize_error;

            pos += pos_offset - 1;
        }
        else if (IS_ALPHA(line[pos]))
        {
            pos_offset = parse_name(&t, line, pos);

            if (pos_offset == 0)
                goto tokenize_error;

            pos += pos_offset - 1;
        }
        else if (IS_OPERATOR(line[pos]))
        {
            pos_offset = parse_operator(&t, line, pos); 

            if (pos_offset == 0)
                goto tokenize_error;

            pos += pos_offset - 1;
        }
        else if (IS_ENCLOSURE(line[pos]))
        {
            pos_offset = parse_enclosure(&t, line, pos);

            if (pos_offset == 0)
                goto tokenize_error;

            pos += pos_offset - 1;
        }
        else if (IS_SEPARATOR(line[pos]))
        {
            pos_offset = parse_separator(&t, line, pos);

            if (pos_offset == 0)
                goto tokenize_error;

            pos += pos_offset - 1;
        }
        else
        {
            tokenize_error:

            delete_tokens(base);
            base = NULL;

            printf("Error: Count not tokenize line at position %zd\n", pos);
            printf("Character: %c\n", line[pos]);
            printf("%s\n", line);
            break;
        }

        next = malloc(sizeof(struct token));
        memcpy(next, &t, sizeof(struct token));
        
        if (base == NULL)
        {
            base = cur = next;
        }
        else
        {
            cur->next = next;
            cur = next;
        }
    }

    return base;
}


void delete_tokens(struct token *base)
{
    struct token *current, *next;

    current = base;
    while (current != NULL)
    {
        next = current->next;

        free(current->lexeme);
        free(current);

        current = next;
    }
}


size_t parse_number(struct token *t, char *line, size_t pos)
{
    char *raw_number;
    size_t length = 0, capacity = DEFAULT_MAX_LEX_LENGTH;
    int decimal = 0;

    if (t == NULL || line == NULL)
        return 0;

    raw_number = malloc(capacity);

    while (IS_NUMBER(line[pos]) || (line[pos] == '.' && !decimal))
    {
        if (line[pos] == '.')
            decimal = 1;

        raw_number[length++] = line[pos++];

        // capacity - 1 so we ensure space for '\0'
        if (length >= capacity - 1)
        {
            capacity *= 2;
            raw_number = realloc(raw_number, capacity);
        }
    }

    raw_number[length] = '\0';

    t->lexeme = raw_number;
    t->length = length; 
    t->flag = TOKEN_FLAG_NUMBER;
    t->next = NULL;

    return length;
}


size_t parse_name(struct token *t, char *line, size_t pos)
{
    char *raw_name;
    size_t length = 0, capacity = DEFAULT_MAX_LEX_LENGTH;

    if (t == NULL || line == NULL)
        return 0;

    raw_name = malloc(capacity);

    while (IS_ALPHA(line[pos]) || (IS_NUMBER(line[pos]) && length > 0))
    {
        raw_name[length++] = line[pos++];

        // capacity - 1 so we ensure space for '\0'
        if (length >= capacity - 1)
        {
            capacity *= 2;
            raw_name = realloc(raw_name, capacity);
        }
    }

    raw_name[length] = '\0';

    t->lexeme = raw_name;
    t->length = length;
    t->flag = TOKEN_FLAG_NAME;
    t->next = NULL;

    return length;
}


size_t parse_operator(struct token *t, char *line, size_t pos)
{
    char *raw_op;
    size_t length = 0, capacity = DEFAULT_MAX_LEX_LENGTH;

    if (t == NULL || line == NULL)
        return 0;

    raw_op = malloc(capacity);

    while (IS_OPERATOR(line[pos]))
    {
        raw_op[length++] = line[pos++];

        // capacity - 1 so we ensure space for '\0'
        if (length >= capacity - 1)
        {
            capacity *= 2;
            raw_op = realloc(raw_op, capacity);
        }
    }

    raw_op[length] = '\0';

    t->lexeme = raw_op;
    t->length = length;
    t->flag = TOKEN_FLAG_OP;
    t->next = NULL;

    return length;
}


size_t parse_enclosure(struct token *t, char *line, size_t pos)
{
    char *raw_enc;

    if (t == NULL || line == NULL)
        return 0;

    raw_enc = malloc(2);
    raw_enc[0] = line[pos];
    raw_enc[1] = '\0';

    t->lexeme = raw_enc;
    t->length = 1;
    t->flag = TOKEN_FLAG_ENCLOSURE;
    t->next = NULL;

    if (line[pos] == '(' || line[pos] == '[' || line[pos] == '{')
    {
        t->orientation = -1;
    }
    else
    {
        t->orientation = 1;
    }

    return 1;
}


size_t parse_separator(struct token *t, char *line, size_t pos)
{
    char *raw_sep;

    raw_sep = malloc(2);
    raw_sep[0] = line[pos];
    raw_sep[1] = '\0';

    t->lexeme = raw_sep;
    t->length = 1;
    t->flag = TOKEN_FLAG_SEPARATOR;
    t->next = NULL;

    return 1;
}
