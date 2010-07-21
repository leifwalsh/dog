#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROG() (prog ? prog : argv[0])

#define PERROR() perror(PROG())

#define PFAIL()                                 \
    do {                                        \
        PERROR();                               \
        ret = errno;                            \
        goto cleanup;                           \
    } while (0)

#define PFAILIF(cond)                           \
    do {                                        \
        if (cond) {                             \
            PFAIL();                            \
        }                                       \
    } while (0)

#define ERR(fmt, ...) fprintf(stderr, "%s: " fmt, PROG(), __VA_ARGS__)

#define FAIL(ret_, fmt, ...)                    \
    do {                                        \
        ERR(fmt, __VA_ARGS__);                  \
        ret = (ret_);                           \
        goto cleanup;                           \
    } while (0)

#define FAILIF(cond, ret_, fmt, ...)            \
    do {                                        \
        if (cond) {                             \
            FAIL((ret_), fmt, __VA_ARGS__);     \
        }                                       \
    } while (0)

#define malloc_chk(p, type, sz)                 \
    do {                                        \
        (p) = (type *) malloc(sz);              \
        PFAILIF(!(p));                          \
    } while (0)

#define free_chk(p)                             \
    do {                                        \
        if (p) {                                \
            free(p);                            \
            (p) = NULL;                         \
        }                                       \
    } while (0)


int main(int argc, char *argv[])
{
    int ret = 0;
    char *prog = NULL;
    char filename[20] = "/tmp/dog_tmp_XXXXXX";
    int fd = -1;
    ssize_t sz_read = 0;
    ssize_t sz_written = 0;
    char *buf = NULL;
    long page_size = 0;

    /* lengthy */
    {
        char *tmp1 = NULL;
        char *tmp2 = NULL;
        tmp1 = strdup(argv[0]);
        tmp2 = basename(tmp1);
        prog = strdup(tmp2);
        free_chk(tmp1);
    }

    FAILIF((argc > 1), 2, "invalid argument: %s\n", argv[1]);

    PFAILIF((fd = mkstemp(filename)) < 0);
    page_size = getpagesize();
    malloc_chk(buf, char, page_size);
    while ((sz_read = read(STDIN_FILENO, buf, page_size)) > 0) {
        while (sz_read) {
            sz_written = write(fd, buf, sz_read);
            PFAILIF(sz_written < 0);
            sz_read -= sz_written;
        }
    }
    PFAILIF(sz_read < 0);

    /* success! */
    printf("%s\n", filename);
cleanup:
    free_chk(buf);
    if (fd >= 0) {
        PFAILIF(close(fd) < 0);
    }
    free_chk(prog);
    exit(ret);
}
