/* June 2, 2019 */

#ifndef CHECKSUM_H
#define CHECKSUM_H

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define HERE __func__, __FILE__, __LINE__

typedef enum { METH_STREAM, METH_MMAP } method_t;
typedef enum { ACTION_CHECKSUM, ACTION_COMPARE } action_t;

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

/* Compare two files via file streaming */
int ck_cmp_stream(int fd1, int fd2);

/* Compare two files via file mapping */
int ck_cmp_mmap(int fd1, int fd2);

/* Get size of a file descriptor */
off_t ck_fsize(int fd);

/* Check that a file descriptor is a regular file */
int ck_fregular(int fd);

/* Open a file descriptor */
int ck_open(const char * pathname);

/* Print error and abort */
__attribute__((noreturn)) void ck_error(const char * s);

/* Abort due to internal error */
__attribute__((noreturn)) void ck_abort(const char * func, const char * file, int line);

#endif /* CHECKSUM_H */
