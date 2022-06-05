#include <stdint.h>
#include <stddef.h>

#include <fuzzer/FuzzedDataProvider.h>

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

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {
    // Ensure a minimum data length
    if(Size < 100) return 0;

    // Setup FuzzedDataProvider and initialize the mocklib
    FuzzedDataProvider fuzz_data_provider(Data, Size);
    FuzzedDataProvider *fuzz_data = &fuzz_data_provider;

    int number_of_functions = fuzz_data->ConsumeIntegralInRange<int>(1,100);
    for (int i=0; i<number_of_functions; i++) {
        int func_id = fuzz_data->ConsumeIntegralInRange<int>(0, 19);
        switch(func_id) {
            case 0: {
                uint8_t fuzz_bytes_0[12] = {0};
                ConsumeDataAndFillRestWithZeros(fuzz_bytes_0, 12, fuzz_data);
                uint8_t fuzz_bytes_1[64] = {0};
                ConsumeDataAndFillRestWithZeros(fuzz_bytes_1, 64, fuzz_data);
                GPS_driver_obtain_current_position(fuzz_bytes_0, fuzz_bytes_1);
                break;
            }
            case 1: {
                HSM_get_random_byte();
                break;
            }
            case 2: {
                driver_get_current_time();
                break;
            }
            case 3: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                char fuzz_bytes_0[64] = {0};
                ConsumeDataAndFillRestWithZeros(fuzz_bytes_0, 64, fuzz_data);
                char fuzz_bytes_1[64] = {0};
                ConsumeDataAndFillRestWithZeros(fuzz_bytes_1, 64, fuzz_data);
                uint8_t fuzz_bytes_2[64] = {0};
                ConsumeDataAndFillRestWithZeros(fuzz_bytes_2, 64, fuzz_data);
                third_party_library_calc_hmac(fuzz_data_0.data(), fuzz_size_0, fuzz_bytes_0, fuzz_bytes_1, fuzz_bytes_2);
                break;
            }
            case 4: {
                GPS::position struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                GPS::get_current_position(&struct_0);
                break;
            }
            case 5: {
                GPS::get_destination_position();
                break;
            }
            case 6: {
                GPS::init_crypto_module();
                break;
            }
            case 7: {
                GPS::position struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                GPS::set_destination_position(struct_0);
                break;
            }
            case 8: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                crypto::hmac struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::calculate_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
                break;
            }
            case 9: {
                crypto::get_state();
                break;
            }
            case 10: {
                crypto::init();
                break;
            }
            case 11: {
                crypto::key struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::set_key(struct_0);
                break;
            }
            case 12: {
                crypto::nonce struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::set_nonce(struct_0);
                break;
            }
            case 13: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                crypto::hmac struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::verify_hmac(fuzz_data_0.data(), fuzz_size_0, &struct_0);
                break;
            }
            case 14: {
                crypto::key struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::verify_key(struct_0);
                break;
            }
            case 15: {
                crypto::nonce struct_0 = {0};
                ConsumeDataAndFillRestWithZeros(&struct_0, sizeof(struct_0), fuzz_data);
                crypto::verify_nonce(&struct_0);
                break;
            }
            case 16: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                key_management::create_key(fuzz_data_0.data(), fuzz_size_0);
                break;
            }
            case 17: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                key_management::create_nonce(fuzz_data_0.data(), fuzz_size_0);
                break;
            }
            case 18: {
                std::vector<uint8_t> fuzz_data_0 = fuzz_data->ConsumeBytes<uint8_t>(fuzz_data->ConsumeIntegral<uint8_t>());
                size_t fuzz_size_0 = fuzz_data_0.size();
                key_management::generate_random_bytes(fuzz_data_0.data(), fuzz_size_0);
                break;
            }
            case 19: {
                time_management::current_time();
                break;
            }
        }
    }

    return 0;
}
