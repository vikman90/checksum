/* June 2, 2019 */

#include "checksum.h"

/* Compute checksum via file mapping */
uint32_t ck_mmap(int fd) {
    struct stat buf;
    unsigned char * data;
    uint32_t checksum;

    assert(fd > 0);

    if (fstat(fd, &buf) == -1) {
        perror("stat");
        abort();
    }

    data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (data == NULL) {
        perror("Cannot map file into memory");
        abort();
    }

    checksum = adler32(data, buf.st_size);
    munmap(data, buf.st_size);
    return checksum;
}
