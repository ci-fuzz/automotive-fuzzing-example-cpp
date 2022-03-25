#!/bin/sh

export BUILD_FUZZERS=true
export FUZZING_ENGINE=libfuzzer
export SANITIZER=address
export ASAN_OPTIONS=detect_leaks=0:verify_asan_link_order=0
export CC=/opt/ci-fuzz-2.30.0/bin/clang
export CXX=/opt/ci-fuzz-2.30.0/bin/clang++
export CFLAGS="-fsanitize=fuzzer-no-link,address -O0"
export CXXFLAGS="-fsanitize=fuzzer-no-link,address -O0"
export LDFLAGS="-fsanitize=address"
export LIB_FUZZING_ENGINE=-fsanitize=fuzzer