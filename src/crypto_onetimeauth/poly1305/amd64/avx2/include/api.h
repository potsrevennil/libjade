#ifndef JADE_ONETIMEAUTH_POLY1305_AMD64_AVX2_API_H
#define JADE_ONETIMEAUTH_POLY1305_AMD64_AVX2_API_H

#define JADE_ONETIMEAUTH_POLY1305_AMD64_AVX2_BYTES 16
#define JADE_ONETIMEAUTH_POLY1305_AMD64_AVX2_KEYBYTES 32
#define JADE_ONETIMEAUTH_POLY1305_AMD64_AVX2_ALGNAME "Poly1305"

#include <stdint.h>

int jade_onetimeauth_poly1305_amd64_avx2(
 uint8_t *out, /*BYTES*/
 uint8_t *in,
 uint64_t inlen,
 uint8_t *key /*KEYBYTES*/
);

int jade_onetimeauth_poly1305_amd64_avx2_verify(
 uint8_t *h, /*BYTES*/
 uint8_t *in,
 uint64_t inlen,
 uint8_t *key /*KEYBYTES*/
);

#endif
