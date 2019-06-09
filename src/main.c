/* June 2, 2019 */

#include "checksum.h"

static const char * file_name;
static const char * file_name_cmp;
static action_t action = ACTION_CHECKSUM;
uint32_t (* ck_callback)(int);
int (* ck_cmp_callback)(int, int);

/* Parse arguments */
static void parse_options(int argc, char ** argv);

/* Show help and exit */
static __attribute__((noreturn)) void help(int status);

/* Main function */
int main(int argc, char ** argv) {
    int fd;
    int fd_cmp;

    parse_options(argc, argv);

    if (file_name) {
        fd = open(file_name, O_RDONLY);
        if (fd == -1) {
            perror("Cannot open file");
            return EXIT_FAILURE;
        }
    } else {
        fd = STDIN_FILENO;
    }

    switch (action) {
    case ACTION_CHECKSUM:
        assert(ck_callback != NULL);
        printf("%x\n", ck_callback(fd));
        break;

    case ACTION_COMPARE:
        assert(ck_cmp_callback != NULL);
        assert(fd != STDIN_FILENO);

        if (file_name_cmp) {
            fd_cmp = open(file_name_cmp, O_RDONLY);
            if (fd_cmp == -1) {
                perror("Cannot open file");
                return EXIT_FAILURE;
            }
        } else {
            fd_cmp = STDIN_FILENO;
        }

        printf("%s\n", ck_cmp_callback(fd, fd_cmp) ? "Files are different" : "Files are similar");
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
    static method_t method = METH_STREAM;

    while ((c = getopt(argc, argv, "chm")) != -1) {
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
        } else if (method == METH_MMAP) {
            fprintf(stderr, "WARN: Standard input does not support memory mapping.\n");
            method = METH_STREAM;
        }

        ck_callback = method == METH_STREAM ? ck_stream : ck_mmap;
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
        } else if (method == METH_MMAP) {
            fprintf(stderr, "WARN: Standard input does not support memory mapping.\n");
            method = METH_STREAM;
        }

        ck_cmp_callback = method == METH_STREAM ? ck_cmp_stream : ck_cmp_mmap;
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
    );

    exit(status);
}
