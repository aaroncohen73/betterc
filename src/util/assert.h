#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

void assert_fail(char *msg);

#define ASSERT_NOT_NULL_ERROR "Null value in function %s"
#define ASSERT_NOT_NULL_ERROR_LEN sizeof(ASSERT_NOT_NULL_ERROR) - 3

void assert_not_null(const char *func_name, int count, ...);
