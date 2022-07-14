#include <assert.h>

#include <cifuzz/cifuzz.h>
#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "crypto_module_1.h"


FUZZ_TEST(const uint8_t *data, size_t size) {

  crypto::init();

  char * key = NULL;
  char * nonce = NULL;
  uint8_t * hmac = NULL;

  third_party_library_calc_hmac(data, size, key, nonce, hmac);
}