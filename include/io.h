#include <sys/ioctl.h>
#include <grp.h>
#include <pwd.h>

struct winsize get_termsize(void);

const char* get_uname(uid_t uid);

const char* get_gname(gid_t gid);
