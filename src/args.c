#include "../include/args.h"

#include <stdio.h>
#include <stdlib.h>

void print_help_and_exit(const char* content, int status)
{
    printf(help, content, optstring);
    exit(status);
    return;
}

arg_values parse_args(int argc, char **argv)
{
    arg_values args;

    // set default options
    args.colormode = COLOR;
    args.printmode = PRETTY;

    // parse arguments
    int opt;
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
            case 'c':
                args.colormode = NOCOLOR;
                break;
            case 'h':
                print_help_and_exit(argv[0], 0);
                break;
            case 'l':
                args.printmode = LIST;
                break;
            case 'p':
                args.printmode = PLAIN;
                break;
            case 'v':
                printf(version_message, version);
                exit(0);
                break;
            case '?':
                print_help_and_exit(argv[0], 1);
                break;
        }
    }

    return args;
}
