#ifndef JADE_KEM_frodo_frodo976shake_amd64_avx2_API_H
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_API_H

#include <stdint.h>

#define JADE_KEM_frodo_frodo976shake_amd64_avx2_SECRETKEYBYTES   31296
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_PUBLICKEYBYTES   15632
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_CIPHERTEXTBYTES  15792
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_KEYPAIRCOINBYTES 88
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_ENCCOINBYTES     72
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_BYTES            24

#define JADE_KEM_frodo_frodo976shake_amd64_avx2_ALGNAME         "Frodo976shake"
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_ARCH            "amd64"
#define JADE_KEM_frodo_frodo976shake_amd64_avx2_IMPL            "avx2"

// kem api
int jade_kem_frodo_frodo976shake_amd64_avx2_keypair_derand(uint8_t *public_key,
                                                           uint8_t *secret_key,
                                                           uint8_t *coins);

int jade_kem_frodo_frodo976shake_amd64_avx2_keypair(uint8_t *public_key,
                                                    uint8_t *secret_key);

int jade_kem_frodo_frodo976shake_amd64_avx2_enc_derand(uint8_t *ciphertext,
                                                       uint8_t *shared_secret,
                                                       uint8_t *public_key,
                                                       uint8_t *coins);

int jade_kem_frodo_frodo976shake_amd64_avx2_enc(uint8_t *ciphertext,
                                                uint8_t *shared_secret,
                                                uint8_t *public_key);

int jade_kem_frodo_frodo976shake_amd64_avx2_dec(uint8_t *shared_secret,
                                                uint8_t *ciphertext,
                                                uint8_t *secret_key);

#endif
