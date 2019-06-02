/* June 2, 2019 */

#include "checksum.h"

/* Compute checksum via file streaming */
uint32_t ck_stream(int fd) {
    struct stat buf;
    unsigned char * data;
    uint32_t checksum;

    if (fstat(fd, &buf) == -1) {
        perror("stat");
        abort();
    }

    data = malloc(buf.st_size);
    if (data == NULL) {
        perror("Cannot allocate memory enough");
        abort();
    }

    if (read(fd, data, buf.st_size) == -1) {
        perror("Cannot read data from file");
        abort();
    }

    checksum = adler32(data, buf.st_size);
    free(data);
    return checksum;
}
