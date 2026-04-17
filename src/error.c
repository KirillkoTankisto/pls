#include "../include/error.h"

#include <stdio.h>

void printerror(const char *function, size_t line, enum ERRORS error)
{
    printf("%s at line %zu: %s\n", function, line, errors[error]);

    return;
}
