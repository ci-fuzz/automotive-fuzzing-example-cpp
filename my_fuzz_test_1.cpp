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
  simpleExample(data, size);
#ifdef FUZZ
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif

    std::cout << "###### FUZZTEST : Finish fuzzing" << std::endl;

}

