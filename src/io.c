#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/error.h"
#include "../include/io.h"

struct winsize get_termsize(void)
{
    struct winsize term;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);

    return term;
}

static const char unknown[] = "unknown";

const char* get_uname(uid_t uid)
{
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);

    if (bufsize == -1)
        bufsize = 16 * 1024;

    buf = malloc(bufsize);
    if (!buf)
    {
        PERR(MALLOC);
        exit(1);
    }

    getpwuid_r(uid, &pwd, buf, bufsize, &result);

    if (!result)
    {
        free(buf);
        return unknown;
    }

    char *name = strdup(result->pw_name);

    free(buf);

    return name;
}

const char* get_gname(gid_t gid)
{
    struct group grp;
    struct group *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
    if (bufsize == -1)
        bufsize = 16 * 1024;

    buf = malloc(bufsize);
    if (!buf)
    {
        PERR(MALLOC);
    }

    getgrgid_r(gid, &grp, buf, bufsize, &result);
    if (!result)
    {
        free(buf);
        return unknown;
    }

    char *name = strdup(result->gr_name);

    free(buf);

    return name;
}
