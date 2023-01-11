#include <dlfcn.h>
#include <iostream>
#include <thread>

#include <cifuzz/cifuzz.h>

#include "target.h"

int print = 1;

// 1. Typedef signature for main function
typedef int (*MainSignature)(int, char **);

FUZZ_TEST_SETUP() {
  // Perform any one-time setup required by the FUZZ_TEST function.

  // 2. Declare signature for the main function with a null pointer
  MainSignature origin_main = nullptr;
  // 3. Obtain the address of the main function from shared object
  origin_main = (MainSignature)dlsym(RTLD_NEXT, "main");
  // 4. If needed prepare arguments for the main function
  char **c;
  // Invoke the origin main function
  //origin_main(1, NULL);
  std::thread(origin_main, 1, c).detach();

}

FUZZ_TEST(const uint8_t *data, size_t size) {
    if (print) {
      std::cout << "############ Start Fuzzing ##############" << std::endl;
      print = 0;
    }
    UBSanFinding(data, size);
}

