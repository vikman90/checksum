/* June 2, 2019 */

#include "checksum.h"

const char * file_name;
method_t method = METH_STREAM;

/* Parse arguments */
static void parse_options(int argc, char ** argv);

/* Show help and exit */
static __attribute__((noreturn)) void help(int status);

/* Main function */
int main(int argc, char ** argv) {
    int fd;
    uint32_t checksum;

    parse_options(argc, argv);

    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("Cannot open file");
        return EXIT_FAILURE;
    }

    switch (method) {
    case METH_STREAM:
        checksum = ck_stream(fd);
        break;

    case METH_MMAP:
        checksum = ck_mmap(fd);
        break;

    default:
        /* This should not occur */
        fprintf(stderr, "Internal error at %s:%d.\n", __FILE__, __LINE__);
        abort();
    }

    printf("%x\n", checksum);
    close(fd);
    return EXIT_SUCCESS;
}

/* Parse arguments */
void parse_options(int argc, char ** argv) {
    int c;

    while ((c = getopt(argc, argv, "hm")) != -1) {
        switch (c) {
        case 'h':
            help(EXIT_SUCCESS);
            /* No return */

        case 'm':
            method = METH_MMAP;
            break;

        case '?':
            /* opterr = 1, so getopt() will print an error */
            break;

        default:
            /* This should not occur */
            fprintf(stderr, "Internal error at %s:%d.\n", __FILE__, __LINE__);
            abort();
        }
    }

    if (optind == argc) {
        help(EXIT_FAILURE);
    }

    file_name = argv[optind];
}

/* Show help and exit */
void help(int status) {
    printf(
        "File checksum - version " VERSION "\n"
        "Usage: checksum [ -h ] [ -m ] <file>\n"
        "Options:\n"
        "   -h  Show this help.\n"
        "   -m  Use memory mapping method.\n"
    );

    exit(status);
}
