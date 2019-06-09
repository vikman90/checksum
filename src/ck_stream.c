/* June 2, 2019 */

#include "checksum.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 65536
#elif BLOCKSIZE < 1
#error The block size must be a positive number.
#endif

/* Compute checksum via file streaming */
uint32_t ck_stream(int fd) {
    unsigned char data[BLOCKSIZE];
    adler32_t ctx;
    ssize_t size;

    adler32_init(&ctx);

    while ((size = read(fd, data, BLOCKSIZE)) > 0) {
        adler32_update(&ctx, data, size);
    }

    return adler32_final(&ctx);
}

/* Compare two files via file streaming */
int ck_cmp_stream(int fd1, int fd2) {
    unsigned char data1[BLOCKSIZE];
    unsigned char data2[BLOCKSIZE];
    ssize_t size1 = read(fd1, data1, BLOCKSIZE);
    ssize_t size2 = read(fd2, data2, BLOCKSIZE);

    while (size1 > 0 && size2 > 0) {
        if (size1 != size2 || memcmp(data1, data2, size1) != 0) {
            return 1;
        }

        size1 = read(fd1, data1, BLOCKSIZE);
        size2 = read(fd2, data2, BLOCKSIZE);
    }

    return size1 != 0 || size2 != 0;
}
