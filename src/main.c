/* June 2, 2019 */

#include "checksum.h"

static const char * file_name;
static const char * file_name_cmp;
static action_t action = ACTION_CHECKSUM;
static method_t method = METH_STREAM;
static algorithm_t algorithm = ALGORITHM_ADLER32;

/* Parse arguments */
static void parse_options(int argc, char ** argv);

/* Show help and exit */
static __attribute__((noreturn)) void help(int status);

/* Main function */
int main(int argc, char ** argv) {
    int fd;
    int fd_cmp;

    parse_options(argc, argv);

    fd = ck_open(file_name);

    switch (action) {
    case ACTION_CHECKSUM:
        if (method == METH_MMAP && !ck_fregular(fd)) {
            fprintf(stderr, "WARN: Memory mapping requires regular files\n");
            method = METH_STREAM;
        }

        hash_t hash = { .algorithm = algorithm };

        if (method == METH_STREAM) {
            ck_stream(&hash, fd);
        } else {
            /* METH_MMAP */
            ck_mmap(&hash, fd);
        }

        for (int i = 0; i < hash.size; ++i) {
            printf("%02x", hash.digest[i]);
        }

        printf("\n");
        break;

    case ACTION_COMPARE:
        fd_cmp = ck_open(file_name_cmp);
        if (method == METH_MMAP && !(ck_fregular(fd) && ck_fregular(fd_cmp))) {
            fprintf(stderr, "WARN: Memory mapping requires regular files\n");
            method = METH_STREAM;
        }

        int answer = method == METH_STREAM ? ck_cmp_stream(fd, fd_cmp) : ck_cmp_mmap(fd, fd_cmp);
        printf("%s\n", answer ? "Files are different" : "Files are similar");
        close(fd_cmp);
        break;

    default:
        ck_abort(HERE);
    }

    close(fd);
    return EXIT_SUCCESS;
}

/* Parse arguments */
void parse_options(int argc, char ** argv) {
    int c;

    while ((c = getopt(argc, argv, "chmrs")) != -1) {
        switch (c) {
        case 'c':
            action = ACTION_COMPARE;
            break;

        case 'h':
            help(EXIT_SUCCESS);
            /* No return */

        case 'm':
            method = METH_MMAP;
            break;

        case 'r':
            algorithm = ALGORITHM_CRC32;
            break;

        case 's':
            algorithm = ALGORITHM_SHA1;
            break;

        case '?':
            /* opterr = 1, so getopt() will print an error */
            break;

        default:
            /* This should not occur */
            ck_abort(HERE);
        }
    }

    switch (action) {
    case ACTION_CHECKSUM:
        if (optind < argc && strcmp(argv[optind], "-")) {
            file_name = argv[optind];
        }

        break;

    case ACTION_COMPARE:
        if (optind < argc && strcmp(argv[optind], "-")) {
            file_name = argv[optind];
        } else {
            fprintf(stderr, "ERROR: File not defined.\n");
            exit(EXIT_FAILURE);
        }

        optind++;

        if (optind < argc && strcmp(argv[optind], "-")) {
            file_name_cmp = argv[optind];
        }

        break;

    default:
        /* This should not occur */
        ck_abort(HERE);
    }
}

/* Show help and exit */
void help(int status) {
    printf(
        "File checksum - version " VERSION "\n"
        "Usage: checksum [ -h ] [ -m ] [ FILE1 ] [ FILE2 ]\n"
        "   If no file specified or file \"-\" is given, checksum reads stdin.\n"
        "Options:\n"
        "   -h  Show this help.\n"
        "   -c  Compare two files."
        "   -m  Use memory mapping method.\n"
        "   -r  Use CRC-32 hash algorithm.\n"
        "   -s  Use SHA-1 hash algorithm.\n"
    );

    exit(status);
}
