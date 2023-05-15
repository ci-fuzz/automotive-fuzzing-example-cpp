#include <iostream>
#include "my_fuzz_test_1.h"
#include "target.h"


int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  UBSanFinding(data, size);
  return 0;
}

