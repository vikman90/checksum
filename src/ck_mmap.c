/* June 2, 2019 */

#include "checksum.h"

/* Compute checksum via file mapping */
uint32_t ck_mmap(int fd) {
    size_t size = ck_fsize(fd);
    unsigned char * data = mmap(NULL, size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);

    if (data == NULL) {
        ck_error("Cannot map file into memory");
    }

    uint32_t checksum = adler32(data, size);
    munmap(data, size);
    return checksum;
}

/* Compare two files via file mapping */
int ck_cmp_mmap(int fd1, int fd2) {
    size_t size1 = ck_fsize(fd1);
    size_t size2 = ck_fsize(fd2);

    if (size1 != size2) {
        return 1;
    }

    unsigned char * data1 = mmap(NULL, size1, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd1, 0);
    unsigned char * data2 = mmap(NULL, size2, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd2, 0);

    if (data1 == NULL || data2 == NULL) {
        ck_error("Cannot map file into memory");
    }

    int result = memcmp(data1, data2, size1 < size2 ? size1 : size2);
    munmap(data1, size1);
    munmap(data2, size2);
    return result != 0;
}
