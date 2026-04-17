#include "../include/dirs.h"
#include "../include/error.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

entries_t *get_dir(const char* path, enum COLORMODE colormode, some_map *umap, some_map *gmap)
{


    DIR *dir = opendir(path);
    if (!dir) return NULL;

    int dir_fd = dirfd(dir);
    if (dir_fd < 0) return NULL;

    entries_t *entries = create_entries(32);

    dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // skip "." and ".."
        if (entry->d_name[0] == '.' &&
            (entry->d_name[1] == '\0' ||
            (entry->d_name[1] == '.' && entry->d_name[2] == '\0')))
            continue;

        entry_object obj = get_entry(entry->d_name, dir_fd, umap, gmap, colormode);

        push_entries(entries, &obj);
    }

    closedir(dir);

    return entries;
}

entry_object get_entry(const char *name, int dir_fd, some_map *umap, some_map *gmap, enum COLORMODE colormode)
{
    entry_object obj;

    obj.name = strdup(name);

    set_metadata(dir_fd, &obj, umap, gmap);

    if (colormode == COLOR)
        obj.color = get_color(obj.type);

    return obj;
}

entries_t *create_entries(size_t capacity)
{
    entries_t *entries = malloc(sizeof(entries_t));
    if (!entries)
    {
        PERR(MALLOC);
        exit(1);
    }

    entry_object *entry_objects = malloc(capacity * sizeof(entry_object));
    if (!entry_objects)
    {
        PERR(MALLOC);
        exit(1);
    }

    entries->obj = entry_objects;
    entries->length = 0;
    entries->capacity = capacity;

    return entries;
}

void push_entries(entries_t *entries, entry_object *obj)
{
    if (entries->length == entries->capacity)
    {
        entry_object *tmp = realloc(entries->obj, entries->capacity * 2 * sizeof(entry_object));
        if (!tmp)
        {
            PERR(REALLOC);
            exit(1);
        }

        entries->obj = tmp;
        entries->capacity *=2;
    }

    entries->obj[entries->length] = *obj;

    entries->length += 1;

    return;
}

static int cmp_entry(const void *p1, const void *p2)
{
    const entry_object *obj1 = p1;
    const entry_object *obj2 = p2;

    return strcmp(obj1->name, obj2->name);
}

void sort_dir(entries_t *e)
{
    qsort(e->obj, e->length, sizeof(entry_object), cmp_entry);
    return;
}
