#include "../include/error.h"
#include "../include/genericmap.h"
#include "../include/io.h"

#include <string.h>

some_map create_map(size_t data_size, size_t capacity)
{
    some_map map = {0};

    map.data = malloc(data_size * capacity);
    if (!map.data)
    {
        PERR(MALLOC);
        exit(1);
    }

    map.data_size = data_size;
    map.length = 0;
    map.capacity = capacity;

    return map;
}

void push_map(some_map *map, void *value)
{
    if (map->length == map->capacity)
    {
        char *tmp = realloc(map->data, map->capacity * map->data_size * 2);
        if (!tmp)
        {
            PERR(MALLOC);
            exit(1);
        }

        map->data = tmp;
        map->capacity *= 2;
    }

    memcpy(map->data + (map->length * map->data_size), value, map->data_size);

    map->length += 1;

    return;
}

void *get_map(some_map *map, size_t id)
{
    char *base = map->data;

    for (size_t i = 0; i < map->length; i++)
    {
        size_t current_id;
        memcpy(&current_id, base + i * map->data_size, sizeof(size_t));

        if (current_id == id)
            return base + i * map->data_size;
    }

    return NULL;
}

const char *get_guid_cached(some_map *map, size_t guid)
{
    struct guid_entry *e = get_map(map, guid);
    if (!e)
    {
        const char *name = get_uname(guid);
        struct guid_entry new =
        {
            .id = guid,
            .value = name,
        };

        push_map(map, &new);

        return name;
    }

    return e->value;
}
