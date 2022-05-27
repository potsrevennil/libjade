#include "api.h"
#include "randombytes.h"
#include "namespace.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//

#define CRYPTO_KEYBYTES NAMESPACE(KEYBYTES)
#define CRYPTO_NONCEBYTES NAMESPACE(NONCEBYTES)
#define CRYPTO_ALGNAME NAMESPACE(ALGNAME)

#define crypto_stream_xor NAMESPACE_LC(xor)
#define crypto_stream JADE_NAMESPACE_LC

#define xstr(s,e) str(s)#e
#define str(s) #s

//

#ifndef LOOPS
#define LOOPS 3
#endif

#ifndef MINBYTES
#define MINBYTES 32
#endif

#ifndef MAXBYTES
#define MAXBYTES 16384
#endif

#ifndef TIMINGS
#define TIMINGS 256
#endif

#define OP 2

//

#define inc_32 inc
#include "increment.c"
#include "cpucycles.c"
#include "printbench.c"

//

int main(void)
{
  int loop, r, i;
  char *op_str[] = {xstr(crypto_stream,.csv), xstr(crypto_stream_xor,.csv)};
  uint8_t ciphertext[MAXBYTES], plaintext[MAXBYTES],
          nonce[CRYPTO_NONCEBYTES], key[CRYPTO_KEYBYTES];
  size_t len;
  uint64_t cycles[TIMINGS];
  uint64_t* results[OP][LOOPS];

  alloc_3(results, size_inc_32(MINBYTES,MAXBYTES));

  for(loop = 0; loop < LOOPS; loop++)
  { for (len = MINBYTES, r = 0; len <= MAXBYTES; len += inc(len), r += 1)
    { for (i = 0; i < TIMINGS; i++)
      { cycles[i] = cpucycles();
        crypto_stream(ciphertext, len, nonce, key); }
      results[0][loop][r] = cpucycles_median(cycles, TIMINGS);

      for (i = 0; i < TIMINGS; i++)
      { cycles[i] = cpucycles();
        crypto_stream_xor(ciphertext, plaintext, len, nonce, key); }
      results[1][loop][r] = cpucycles_median(cycles, TIMINGS);
    }
  }

  cpucycles_fprintf_3(results, op_str);
  free_3(results);

  return 0;
}

