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
