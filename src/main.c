#include "../include/args.h"
#include "../include/dirs.h"
#include "../include/display.h"
#include "../include/error.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

static const char default_path[] = ".";

int perform_list(const char *path, enum COLORMODE colormode, enum PRINTMODE printmode, some_map *umap, some_map *gmap)
{
    struct stat st;

    if (!lstat(path, &st))
    {
        if (S_ISDIR(st.st_mode))
        {
            entries_t *e = get_dir(path, colormode, umap, gmap);

            if (!e)
            {
                PERR(NONEXIST);
                return 1;
            }

            sort_dir(e);

            print_dir(e, printmode, colormode);
        }

        else
        {
            entry_object obj = get_entry(path, st.st_ino, umap, gmap, colormode);

            print_entry(path, &obj, colormode);
        }
    }

    else
        PERR(NONEXIST);
        return 1;

    return 0;
}

int main(int argc, char **argv)
{
    arg_values args = parse_args(argc, argv);

    // create maps for caching getpwuid_r and getgrgid_r syscalls
    some_map umap = create_map(sizeof(struct guid_entry), 32);
    some_map gmap = create_map(sizeof(struct guid_entry), 32);

    if (argc - optind > 1)
    {
        for (; optind < argc; optind++)
        {
            printf("%s:\n", argv[optind]);
            perform_list(argv[optind], args.colormode, args.printmode, &umap, &gmap);
            if (optind + 1 != argc)
                putchar('\n');
        }
    }

    else if (argc - optind == 1)
        return perform_list(argv[optind], args.colormode, args.printmode, &umap, &gmap);

    else
        return perform_list(default_path, args.colormode, args.printmode, &umap, &gmap);

    return 0;
}
