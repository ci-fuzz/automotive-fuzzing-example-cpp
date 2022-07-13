#include <assert.h>

#include <cifuzz/cifuzz.h>
#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

#include "GPS_module_1.h"
#include "crypto_module_1.h"
#include "crypto_module_2.h"
#include "key_management_module_1.h"
#include "time_module_1.h"

// Wrapper function for FuzzedDataProvider.h
// Writes |num_bytes| of input data to the given destination pointer. If there
// is not enough data left, writes all remaining bytes and fills the rest with zeros.
// Return value is the number of bytes written.
void ConsumeDataAndFillRestWithZeros(void *destination, size_t num_bytes, FuzzedDataProvider *fuzz_data) {
  if (destination != nullptr) {
    size_t num_bytes_with_fuzz_data = fuzz_data->ConsumeData(destination, num_bytes);
    if (num_bytes > num_bytes_with_fuzz_data) {
      size_t num_bytes_with_zeros = num_bytes - num_bytes_with_fuzz_data;
      std::memset((char*)destination+num_bytes_with_fuzz_data, 0, num_bytes_with_zeros);
    }
  }
}

FUZZ_TEST(const uint8_t *data, size_t size) {

  crypto::init();

  char * key = NULL;
  char * nonce = NULL;
  uint8_t * hmac = NULL;

  third_party_library_calc_hmac(data, size, key, nonce, hmac);
}