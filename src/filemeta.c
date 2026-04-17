#include "../include/dirs.h"
#include "../include/io.h"

#include <linux/limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum FILETYPE get_filetype(struct stat *st)
{
    if      (S_ISBLK(st->st_mode))  return FT_BLK;
    else if (S_ISCHR(st->st_mode))  return FT_CHR;
    else if (S_ISDIR(st->st_mode))  return FT_DIR;
    else if (S_ISFIFO(st->st_mode)) return FT_FIFO;
    else if (S_ISLNK(st->st_mode))  return FT_LNK;
    else if (S_ISREG(st->st_mode))  return FT_REG;
    else if (S_ISSOCK(st->st_mode)) return FT_SOCK;
    else                            return FT_UNKNOWN;
}

enum COLORS get_color(enum FILETYPE type)
{
    switch (type)
    {
        case FT_BLK:
        case FT_CHR:
        case FT_FIFO:
        case FT_SOCK:
            return YELLOW;

        case FT_DIR:
            return BLUE;

        case FT_LNK:
            return CYAN;

        case FT_REG:
            return GREEN;

        case FT_UNKNOWN:
        default:
            return RED;
    }
}

void set_mode(char txt[11], struct stat *st)
{
    memset(txt, '-', 10);

    switch (get_filetype(st))
    {
        case FT_BLK:
            txt[0] = 'b';
            break;
        case FT_CHR:
            txt[0] = 'c';
            break;
        case FT_DIR:
            txt[0] = 'd';
            break;
        case FT_FIFO:
            txt[0] = 'p';
            break;
        case FT_LNK:
            txt[0] = 'l';
            break;
        case FT_SOCK:
            txt[0] = 's';
            break;
        default:
            break;
    }

    if (st->st_mode & S_IRUSR) txt[1] = 'r';
    if (st->st_mode & S_IWUSR) txt[2] = 'w';
    if (st->st_mode & S_IXUSR) txt[3] = 'x';

    if (st->st_mode & S_IRGRP) txt[4] = 'r';
    if (st->st_mode & S_IWGRP) txt[5] = 'w';
    if (st->st_mode & S_IXGRP) txt[6] = 'x';

    if (st->st_mode & S_IROTH) txt[7] = 'r';
    if (st->st_mode & S_IWOTH) txt[8] = 'w';
    if (st->st_mode & S_IXOTH) txt[9] = 'x';

    txt[10] = '\0';

    return;
}

const char *get_link(int dir_fd, entry_object *e)
{
    const char *result = NULL;
    char buf[PATH_MAX];

    if (readlinkat(dir_fd, e->name, buf, sizeof(buf)) != -1)
    {
        result = strdup(buf);
    }

    return result;
}

void set_metadata(int dir_fd, entry_object *e, some_map *umap, some_map *gmap)
{
    struct stat st;

    if (fstatat(dir_fd, e->name, &st, AT_SYMLINK_NOFOLLOW)) return;

    set_mode(e->mode, &st);

    e->type = get_filetype(&st);
    e->uname = get_guid_cached(umap, st.st_uid);
    e->gname = get_guid_cached(gmap, st.st_gid);
    e->ctime = format_date(&st.st_ctim);
    e->softlink = get_link(dir_fd, e);
    e->hardlinks = st.st_nlink;
    e->size = st.st_size;

    return;
}
