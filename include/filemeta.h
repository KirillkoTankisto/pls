#include <stdlib.h>
#include <sys/stat.h>

#include "genericmap.h"

enum FILETYPE {
    FT_BLK,
    FT_CHR,
    FT_DIR,
    FT_FIFO,
    FT_LNK,
    FT_REG,
    FT_SOCK,
    FT_UNKNOWN
};

enum COLORS
{
    RESET,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
};

static const char *const COLORS_STR[] =
{
    "\x1b[0m",
    "\x1b[30m",
    "\x1b[31m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[34m",
    "\x1b[35m",
    "\x1b[36m",
    "\x1b[37m",
};

typedef struct
{
    char mode[11];
    const char *name;
    const char *uname;
    const char *gname;
    const char *ctime;
    const char *softlink;
    size_t hardlinks;
    size_t size;
    enum FILETYPE type;
    enum COLORS color;
} entry_object;

typedef struct
{
    entry_object *obj;
    size_t length;
    size_t capacity;
} entries_t;

enum FILETYPE get_filetype(struct stat *st);

enum COLORS get_color(enum FILETYPE type);

void set_mode(char txt[11], struct stat *st);

const char *format_date(time_t tvsec);

void set_metadata(int dir_fd, entry_object *e, some_map *umap, some_map *gmap);
