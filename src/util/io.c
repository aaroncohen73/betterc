#include "io.h"

int is_endl(char c)
{
    if (c == '\n' ||
        c == EOF  ||
        c == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int emit(char const *format, ...)
{
    va_list args;
    int written;

    va_start(args, format);

    written = vprintf(format, args);
    printf("\n");

    va_end(args);

    return written;
}

char * read_line(int *length)
{
    char *line;
    int len = 0;
    char lookahead;
    
    line = malloc(DEFAULT_LINE_SIZE);
    
    do
    {
        lookahead = getchar();
        
        if (len >= DEFAULT_LINE_SIZE)
        {
            line = realloc(line, DEFAULT_LINE_SIZE * ((len / 100) + 1));
        }

        line[len++] = lookahead;
    } while (!is_endl(lookahead));

    //Strip line end character and replace w/ null
    line[len - 1] = '\0';

    if (length != NULL) *length = len;

    return line;
}
