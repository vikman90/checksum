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
    adler32_t ctx = ADLER32_INITIALIZER;
    ssize_t size;

    while ((size = read(fd, data, BLOCKSIZE)) > 0) {
        adler32_update(&ctx, data, size);
    }

    return adler32_final(&ctx);
}
