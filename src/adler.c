/* June 2, 2019
 * https://en.wikipedia.org/wiki/Adler-32
 */

#include "checksum.h"

const uint32_t MOD_ADLER = 65521;

/* Compute Adler32 checksum */
uint32_t adler32(unsigned char *data, size_t len) {
    uint32_t a = 1, b = 0;
    size_t index;

    // Process each byte of the data in order
    for (index = 0; index < len; ++index) {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}
