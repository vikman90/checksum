/* June 2, 2019 */

#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define VERSION "0.1"

typedef enum { METH_STREAM, METH_MMAP } method_t;

/* Compute Adler32 checksum */
uint32_t adler32(unsigned char *data, size_t len);

/* Compute checksum via file streaming */
uint32_t ck_stream(int fd);

/* Compute checksum via file mapping */
uint32_t ck_mmap(int fd);

#endif /* CHECKSUM_H */
