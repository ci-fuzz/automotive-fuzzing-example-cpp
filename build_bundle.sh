#!/bin/bash
if [[ -z "$FUZZ_TEST_LDFLAGS" ]]; then
    echo "FUZZ_TEST_LDFLAGS needs to be set!"
    exit 1
fi
# This is a very bad hack to check if we are currently building
# the fuzzing or coverage target 
SANITIZER="address;undefined"
if [ ${#FUZZ_TEST_LDFLAGS} -eq 17  ]; then
    SANITIZER="coverage"
fi

echo "Building with sanitizer: $SANITIZER"
cmake --build out/build/cifuzz_bundle --target clean
cmake -S . --preset=cifuzz_bundle -D"CIFUZZ_SANITIZERS=$SANITIZER"
cmake --build --preset=build_cifuzz_bundle --target my_fuzz_test_1