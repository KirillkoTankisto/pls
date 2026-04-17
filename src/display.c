#include "../include/display.h"

#include <stdio.h>
#include <string.h>

void print_plain(entries_t *e, enum COLORMODE colormode)
{
    for (size_t i = 0; i < e->length; i++)
    {
        entry_object obj = e->obj[i];

        if (colormode == COLOR)
            printf("%s%s%s ", COLORS_STR[obj.color], obj.name, COLORS_STR[RESET]);
        else
            printf("%s ", obj.name);
    }

    putchar('\n');
}

void print_list(entries_t *e, enum COLORMODE colormode)
{
    for (size_t i = 0; i < e->length; i++)
    {
        entry_object obj = e->obj[i];
        if (colormode == COLOR)
        {
            printf("%s %-4zu %-12s %-12s %18zu %s %s%s%s", obj.mode, obj.hardlinks, obj.uname, obj.gname, obj.size, obj.ctime, COLORS_STR[obj.color], obj.name, COLORS_STR[RESET]);

            if (obj.softlink)
                printf(" -> %s%s%s\n", COLORS_STR[obj.color], obj.softlink, COLORS_STR[RESET]);
            else
                putchar('\n');
        }
        else
        {
            printf("%s %-4zu %-12s %-12s %18zu %s %s", obj.mode, obj.hardlinks, obj.uname, obj.gname, obj.size, obj.ctime, obj.name);

            if (obj.softlink)
                printf("-> %s%s%s\n", COLORS_STR[obj.color], obj.softlink, COLORS_STR[RESET]);
            else
                putchar('\n');
        }

    }
}

void print_pretty(entries_t *e, enum COLORMODE colormode)
{
    size_t count = 0;
    size_t maxlen = 0;

    for (size_t i = 0; i < e->length; i++)
    {
        entry_object obj = e->obj[i];
        size_t len = strlen(obj.name);

        if (len > maxlen)
            maxlen = len;

        count++;
    }

    if (count == 0)
        return;

    struct winsize ws = get_termsize();
    size_t termw = ws.ws_col ? ws.ws_col : 80;

    size_t colw = maxlen + 2;
    size_t cols = termw / colw;
    if (cols == 0) cols = 1;

    size_t rows = (count + cols - 1) / cols;

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols; col++)
        {
            size_t idx = col * rows + row;
            if (idx >= count)
                continue;

            entry_object obj = e->obj[idx];

            if (colormode == COLOR)
                printf("%s%s%s", COLORS_STR[obj.color], obj.name, COLORS_STR[RESET]);
            else
                printf("%s", obj.name);

            if (col != cols - 1)
            {
                size_t len = strlen(obj.name);

                size_t pad = colw - len;
                while (pad--) putchar(' ');
            }
        }

        putchar('\n');
    }
}

int print_dir(entries_t *e, enum PRINTMODE printmode, enum COLORMODE colormode)
{
    switch (printmode)
    {
        case PLAIN:
            print_plain(e, colormode);
            break;
        case LIST:
            print_list(e, colormode);
            break;
        case PRETTY:
            print_pretty(e, colormode);
            break;
    }

    return 0;
}

void print_entry(const char *path, entry_object *obj, enum COLORMODE colormode)
{
    if (colormode == COLOR)
    {
        printf("%s %zu %-6s %6s %18zu %s %s%s%s", obj->mode, obj->hardlinks, obj->uname, obj->gname, obj->size, obj->ctime, COLORS_STR[obj->color], path, COLORS_STR[RESET]);

        if (obj->softlink)
            printf(" -> %s%s%s\n", COLORS_STR[obj->color], obj->softlink, COLORS_STR[RESET]);

        else
            putchar('\n');
    }

    else
    {
        printf("%s %zu %-6s %6s %18zu %s %s", obj->mode, obj->hardlinks, obj->uname, obj->gname, obj->size, obj->ctime, path);

        if (obj->softlink)
            printf(" -> %s\n", obj->softlink);

        else
            putchar('\n');
    }

    return;
}
