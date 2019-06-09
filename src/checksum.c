/* June 9, 2019 */

#include "checksum.h"

/* Get size of a file descriptor */
off_t ck_fsize(int fd) {
    struct stat buf;

    assert(fd > 0);

    if (fstat(fd, &buf) == -1) {
        ck_error("stat");
    }

    return buf.st_size;
}

/* Check that a file descriptor is a regular file */
int ck_fregular(int fd) {
    struct stat buf;

    if (fstat(fd, &buf) == -1) {
        ck_error("stat");
    }

    return S_ISREG(buf.st_mode);
}

/* Open a file descriptor */
int ck_open(const char * pathname) {
    if (pathname) {
        int fd = open(pathname, O_RDONLY);
        if (fd == -1) {
            perror("ERROR: Cannot open file");
            exit(EXIT_FAILURE);
        } else {
            return fd;
        }
    } else {
        return STDIN_FILENO;
    }
}

/* Print error and abort */
void ck_error(const char * s) {
    assert(s != NULL);
    fprintf(stderr, "ERROR: %s: %s", s, strerror(errno));
    abort();
}

/* Abort due to internal error */
void ck_abort(const char * func, const char * file, int line) {
    fprintf(stderr, "CRITICAL: Internal error in %s() at %s:%d\n", func, file, line);
    abort();
}
