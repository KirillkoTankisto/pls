#include <stdlib.h>

static const char* const errors[] =
{
    "No such file or directory",
    "Malloc failed",
    "Realloc failed"
};

enum ERRORS
{
    NONEXIST,
    MALLOC,
    REALLOC
};

void printerror(const char *function, size_t line, enum ERRORS error);

#define PERR(err) printerror(__func__, __LINE__, err)
