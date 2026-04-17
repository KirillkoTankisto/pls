#include <stdlib.h>

typedef struct
{
    char *data;
    size_t data_size;
    size_t length;
    size_t capacity;
} some_map;

some_map create_map(size_t data_size, size_t capacity);

void push_map(some_map *map, void *value);

void *get_map(some_map *map, size_t id);

struct guid_entry
{
    size_t id;
    const char *value;
};

const char *get_guid_cached(some_map *map, size_t guid);
