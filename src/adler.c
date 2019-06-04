/* June 2, 2019
 * https://en.wikipedia.org/wiki/Adler-32
 */

#include "checksum.h"

const uint32_t MOD_ADLER = 65521;
const size_t ADLER_CHUNK = 5222;

const adler32_t ADLER32_INITIALIZER = { .a = 1, .b = 0 };

/* Compute Adler-32 checksum */
uint32_t adler32(unsigned char * data, size_t len) {
    uint32_t a = 1, b = 0;
    size_t top;

    assert(data != NULL);

    // Process each byte of the data in order
    for (size_t i = 0; i < len; i = top) {
        top = i + ADLER_CHUNK;
        top = top > len ? len : top;

        for (size_t j = i; j < top; ++j) {
            a += data[j];
            b += a;
        }

        a %= MOD_ADLER;
        b %= MOD_ADLER;
    }

    return (b << 16) | a;
}

/* Initialize Adler-32 context */
void adler32_init(adler32_t * ctx) {
    assert(ctx != NULL);
    *ctx = ADLER32_INITIALIZER;
}

/* Compute partial Adler-32 checksum */
void adler32_update(adler32_t * ctx, unsigned char * data, size_t len) {
    size_t top;

    assert(ctx != NULL);
    assert(data != NULL);

    // Process each byte of the data in order
    for (size_t i = 0; i < len; i = top) {
        top = i + ADLER_CHUNK;
        top = top > len ? len : top;

        for (size_t j = i; j < top; ++j) {
            ctx->a += data[j];
            ctx->b += ctx->a;
        }

        ctx->a %= MOD_ADLER;
        ctx->b %= MOD_ADLER;
    }
}

/* Return the Adler-32 message digest */
uint32_t adler32_final(const adler32_t * ctx) {
    assert(ctx != NULL);
    return (ctx->b << 16) | ctx->a;
}

/* Merge two partial checksum contexts */
void adler32_append(adler32_t * c1, const adler32_t * c2) {
    /* TODO */
}
