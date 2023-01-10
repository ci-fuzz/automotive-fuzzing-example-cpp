#include <dlfcn.h>
#include <iostream>
#include <thread>

#include <cifuzz/cifuzz.h>

#include "target.h"

int print = 1;

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.
  int (*origin_main)(int, char **);
  origin_main = (int (*)(int, char **))dlsym(RTLD_NEXT, "main");
  
  char **c;
  //origin_main(1, NULL);
  std::thread(origin_main, 1, c).detach();

}

FUZZ_TEST(const uint8_t *data, size_t size) {
    if (print) {
      std::cout << "############ Start Fuzzing ##############" << std::endl;
      print = 0;
    }
    hmac(data, size);
}

