/* June 2, 2019
 * https://en.wikipedia.org/wiki/Adler-32
 */

#include "checksum.h"

const uint32_t MOD_ADLER = 65521;

const adler32_t ADLER32_INITIALIZER = { .a = 1, .b = 0 };

/* Compute Adler-32 checksum */
uint32_t adler32(unsigned char * data, size_t len) {
    uint32_t a = 1, b = 0;
    size_t index;

    assert(data != NULL);

    // Process each byte of the data in order
    for (index = 0; index < len; ++index) {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
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
    size_t index;

    assert(ctx != NULL);
    assert(data != NULL);

    // Process each byte of the data in order
    for (index = 0; index < len; ++index) {
        ctx->a = (ctx->a + data[index]) % MOD_ADLER;
        ctx->b = (ctx->b + ctx->a) % MOD_ADLER;
    }
}

/* Return the Adler-32 message digest */
uint32_t adler32_final(const adler32_t * ctx) {
    assert(ctx != NULL);
    return (ctx->b << 16) | ctx->a;
}
