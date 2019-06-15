/* June 2, 2019 */

#include "checksum.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 65536
#elif BLOCKSIZE < 1
#error The block size must be a positive number.
#endif

/* Compute checksum via file streaming */
void ck_stream(hash_t * hash, int fd) {
    unsigned char data[BLOCKSIZE];
    ssize_t size;

    if (hash->algorithm == ALGORITHM_ADLER32) {
        adler32_t ctx;
        adler32_init(&ctx);

        while ((size = read(fd, data, BLOCKSIZE)) > 0) {
            adler32_update(&ctx, data, size);
        }

        adler32_final(&ctx, hash->digest);
        hash->size = 4;
    } else {
        /* ALGORITHM_SHA1 */
        EVP_MD_CTX * ctx = EVP_MD_CTX_new();
        EVP_DigestInit(ctx, EVP_sha1());

        while ((size = read(fd, data, BLOCKSIZE)) > 0) {
            EVP_DigestUpdate(ctx, data, size);
        }

        EVP_DigestFinal_ex(ctx, hash->digest, &hash->size);
        EVP_MD_CTX_free(ctx);
    }
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
