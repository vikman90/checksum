/* June 2, 2019
 * https://en.wikipedia.org/wiki/Adler-32
 */

#include "checksum.h"

const uint32_t MOD_ADLER = 65521;
const size_t ADLER_CHUNK = 5222;

const adler32_t ADLER32_INITIALIZER = { .a = 1, .b = 0 };

/* Compute Adler-32 checksum */
void adler32(unsigned char * data, size_t len, unsigned char digest[4]) {
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

#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
    digest[0] = b >> 8;
    digest[1] = b & 0xFF;
    digest[2] = a >> 8;
    digest[3] = a & 0xFF;
#else
    digest[0] = a & 0xFF;
    digest[1] = a >> 8;
    digest[2] = b & 0xFF;
    digest[3] = b >> 8;
#endif
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

/* Get the Adler-32 message digest */
void adler32_final(const adler32_t * ctx, unsigned char digest[4]) {
    assert(ctx != NULL);

#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
    digest[0] = ctx->b >> 8;
    digest[1] = ctx->b & 0xFF;
    digest[2] = ctx->a >> 8;
    digest[3] = ctx->a & 0xFF;
#else
    digest[0] = ctx->a & 0xFF;
    digest[1] = ctx->a >> 8;
    digest[2] = ctx->b & 0xFF;
    digest[3] = ctx->b >> 8;
#endif
}
