/* June 2, 2019 */

#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define VERSION "0.2"

typedef enum { METH_STREAM, METH_MMAP } method_t;

typedef struct {
    uint32_t a;
    uint32_t b;
} adler32_t;

extern const adler32_t ADLER32_INITIALIZER;

/* Compute Adler-32 checksum */
uint32_t adler32(unsigned char * data, size_t len);

/* Initialize Adler-32 context */
void adler32_init(adler32_t * ctx);

/* Compute partial Adler-32 checksum */
void adler32_update(adler32_t * ctx, unsigned char * data, size_t len);

/* Return the Adler-32 message digest */
uint32_t adler32_final(const adler32_t * ctx);

/* Compute checksum via file streaming */
uint32_t ck_stream(int fd);

/* Compute checksum via file mapping */
uint32_t ck_mmap(int fd);

#endif /* CHECKSUM_H */
