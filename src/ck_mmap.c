/* June 2, 2019 */

#include "checksum.h"

typedef struct {
    unsigned char * data;
    size_t len;
    adler32_t ctx;
} ck_threadarg_t;

static void * ck_partial_sum(void * args);

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

uint32_t ck_mmap_mt(int fd) {
    struct stat buf;
    long nproc = sysconf(_SC_NPROCESSORS_ONLN);

    assert(fd > 0);
    assert(nproc > 0);

    pthread_t * threads = malloc(sizeof(pthread_t) * nproc);
    if (threads == NULL) {
        perror("Cannot allocate memory for threads");
        abort();
    }

    ck_threadarg_t * partials = malloc(sizeof(ck_threadarg_t) * nproc);
    if (partials == NULL) {
        perror("Cannot allocate memory for thread data");
        abort();
    }

    if (fstat(fd, &buf) == -1) {
        perror("stat");
        abort();
    }

    unsigned char * data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (data == NULL) {
        perror("Cannot map file into memory");
        abort();
    }

    size_t chunk = buf.st_size / nproc;

    for (int i = 0; i < nproc; ++i) {
        partials[i].data = data + chunk * i;
        partials[i].len = chunk + (i < nproc - 1) ? 0 : buf.st_size - chunk * nproc;

        int error = pthread_create(threads + i, NULL, ck_partial_sum, partials + i);
        if (error) {
            fprintf(stderr, "Cannot start thread: %s\n", strerror(error));
            abort();
        }
    }

    adler32_t ctx = ADLER32_INITIALIZER;

    for (int i = 0; i < nproc; ++i) {
        pthread_join(threads[i], NULL);
        adler32_append(&ctx, &partials[i].ctx);
    }

    munmap(data, buf.st_size);
    free(threads);
    free(partials);

    return adler32_final(&ctx);
}

void * ck_partial_sum(void * args) {
    ck_threadarg_t * partial = (ck_threadarg_t *)args;
    adler32_init(&partial->ctx);
    adler32_update(&partial->ctx, partial->data, partial->len);
    return NULL;
}
