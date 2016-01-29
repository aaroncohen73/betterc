#include "assert.h"

void assert_fail(char *msg)
{
    emit("Assertion failed: %s\n", msg);
    free(msg);
    exit(1);
}

void assert_not_null(const char *func_name, int count, ...)
{
    void *arg;
    char *error_msg;
    va_list args;
    int i, is_null = 0, error_len;

    va_start(args, count);

    for (i = 0; i < count; i++)
    {
        arg = va_arg(args, void *);
        if (arg == NULL)
        {
            is_null = 1;
            break;
        }
    }

    va_end(args);

    if(is_null)
    {
        error_len = ASSERT_NOT_NULL_ERROR_LEN + strlen(func_name) + 1;
        error_msg = malloc(error_len);
        snprintf(error_msg, error_len, ASSERT_NOT_NULL_ERROR, func_name);
        assert_fail(error_msg);
    }
}
