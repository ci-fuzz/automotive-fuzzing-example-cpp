#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

#include <fuzzer/FuzzedDataProvider.h>

#include "GPS_module_1.h"



static FuzzedDataProvider *fuzz_data;

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

// This function received the fuzzer generated data from the fuzz target.
// It needs to be called at the beginning of the LLVMFuzzerTestOneInput function.
void mocklib_set_data(void *fuzzed_data_provider) {
    fuzz_data = (FuzzedDataProvider *) fuzzed_data_provider;
}



