#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

#include <cifuzz/cifuzz.h>

#include "target.h"

#define FUZZ

extern volatile int threadFinished1[num_threads];
extern volatile int threadFinished2[num_threads];

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.
}

FUZZ_TEST(const uint8_t *data, size_t size) {

  std::cout << "###### FUZZTEST : Start fuzzing" << std::endl;
  advancedExample(data, size);

#ifdef FUZZ
    int sum = 0;
    while (1) {
        sum = 0;
        for (int i = 0; i < num_threads; i++){
            sum += threadFinished2[i];
        }
        if (sum == num_threads){
            break;
        }
    }
    // reset status
    for (int i = 0; i < num_threads; i++){
        threadFinished2[i] = 0;
    }
    
#endif

    std::cout << "###### FUZZTEST : Finish fuzzing" << std::endl;

}

