#include <dlfcn.h>
#include <iostream>

#include <cifuzz/cifuzz.h>

#include "target.h"

int print = 1;

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.
  int (*original_main)(int, char **);
  original_main = (int (*)(int, char **))dlsym(RTLD_NEXT, "main");
  
  char **c;
  original_main(1, c);

}

FUZZ_TEST(const uint8_t *data, size_t size) {
    if (print) {
      std::cout << "############ Start Fuzzing ##############" << std::endl;
      print = 0;
    }
    hmac(data, size);
}

