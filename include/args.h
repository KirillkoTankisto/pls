#include <unistd.h>
#include "dirs.h"

static const char version[] = "1.0.0";

static const char optstring[] = "chlpv";

static const char help[] =
"usage: %s [-%s] [DIR] [FILE] ..." "\n"
"  " "-c" "\t" "disable color" "\n"
"  " "-h" "\t" "display this help message" "\n"
"  " "-l" "\t" "show dir in list format" "\n"
"  " "-p" "\t" "show dir in plain format" "\n"
"  " "-v" "\t" "display version info" "\n"
;

static const char version_message[] =
"  " "pls %s" "\n"
"  " "Copyright (C) 2026 KirillkoTankisto." "\n"
"  " "License: GNU GPL Version 3 or later <https://www.gnu.org/licenses/gpl-3.0.html>." "\n"
"  " "This is free software: you're free to change and redistribute it." "\n"
"  " "There is NO WARRANTY, to the extent permitted by law." "\n"
"  " "Report bugs: <https://github.com/KirillkoTankisto/pls/issues>." "\n"
;

void print_help_and_exit(const char* content, int status);

typedef struct
{
    enum PRINTMODE printmode;
    enum COLORMODE colormode;
} arg_values;

arg_values parse_args(int argc, char **argv);
