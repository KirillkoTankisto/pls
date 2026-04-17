#ifndef DIRS_H
#define DIRS_H

#include <dirent.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

#include "filemeta.h"
#include "io.h"

enum COLORMODE
{
    COLOR,
    NOCOLOR
};

enum PRINTMODE
{
    PLAIN,
    LIST,
    PRETTY
};

//

typedef struct dirent dirent;

entries_t *get_dir(const char* path, enum COLORMODE colormode, some_map *umap, some_map *gmap);

entry_object get_entry(const char *name, int dir_fd, some_map *umap, some_map *gmap, enum COLORMODE colormode);

entries_t *create_entries(size_t capacity);

void push_entries(entries_t *entries, entry_object *obj);

void sort_dir(entries_t *e);

#endif
