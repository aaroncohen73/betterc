#include "lexer.h"

list_t tokenize(char *line)
{
    list_t tokens;
    token_t token;
    int line_len, pos;

    tokens = list_create(sizeof(token_t));
    line_len = strlen(line);

    for (pos = 0; pos < line_len; pos++)
    {
        if (IS_WHITE(line[pos]))
        {
            continue;
        }
        else if (IS_NUMBER(line[pos]))
        {
            token = parse_number(line, pos, &pos);
        }
        else if (IS_ALPHA(line[pos]))
        {
            token = parse_name(line, pos, &pos);
        }
        else if (IS_OPERATOR(line[pos]))
        {
            token = parse_operator(line, pos, &pos); 
        }
        else if (IS_ENCLOSURE(line[pos]))
        {
            token = parse_enclosure(line, pos, &pos);
        }
        else if (IS_SEPARATOR(line[pos]))
        {
            token = parse_separator(line, pos, &pos);
        }
        else
        {
            emit("Error: Count not parse line at position %d", pos);
            emit("Character: %c", line[pos]);
            emit("%s", line);
            list_delete(&tokens); // Delete the data so we return an empty list
            break;
        }

        list_add(&tokens, &token);
    }

    return tokens;
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
    token.length = length - 1;
    token.flag = FLAG_NAME;

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
    // TODO: figure out good way to detect operands
    return token;
}
token_t parse_enclosure(char *line, int pos, int *end_pos)
{
    token_t token;
    char *raw_enc;
    
    raw_enc = malloc(2);
    raw_enc[0] = line[pos];
    raw_enc[1] = '\0';
    
    token.lexeme = raw_enc;
    token.length = 1;
    token.flag = FLAG_ENCLOSURE;  

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
token_t parse_separator(char *line, int pos, int *end_pos)
{
    token_t token;
    char *raw_sep;

    raw_sep = malloc(2);
    raw_sep[0] = line[pos];
    raw_sep[1] = '\0';

    token.lexeme = raw_sep;
    token.length = 1;
    token.flag = FLAG_SEPARATOR;

    return token;
}
