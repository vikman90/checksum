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
#include <openssl/evp.h>

#define HERE __func__, __FILE__, __LINE__

typedef enum { METH_STREAM, METH_MMAP } method_t;
typedef enum { ACTION_CHECKSUM, ACTION_COMPARE } action_t;
typedef enum { ALGORITHM_ADLER32, ALGORITHM_SHA1 } algorithm_t;

typedef struct {
    uint32_t a;
    uint32_t b;
} adler32_t;

typedef struct {
    algorithm_t algorithm;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int size;
} hash_t;

extern const adler32_t ADLER32_INITIALIZER;

/* Compute Adler-32 checksum */
void adler32(unsigned char * data, size_t len, unsigned char digest[4]);

/* Initialize Adler-32 context */
void adler32_init(adler32_t * ctx);

/* Compute partial Adler-32 checksum */
void adler32_update(adler32_t * ctx, unsigned char * data, size_t len);

/* Get the Adler-32 message digest */
void adler32_final(const adler32_t * ctx, unsigned char digest[4]);

/* Compute checksum via file streaming */
void ck_stream(hash_t * hash, int fd);

/* Compute checksum via file mapping */
void ck_mmap(hash_t * hash, int fd);

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
