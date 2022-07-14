#!/bin/sh
set -e

# Name of fuzz test
FUZZ_TEST=$1

if test -f "$FUZZ_TEST.cpp"; then

  export CXX=clang++
  export CC=clang
  export CFLAGS="-fprofile-instr-generate -fcoverage-mapping"
  export CXXFLAGS="$CFLAGS"
  export WORK_DIR=.cifuzz-build/llvm_cov
  rm -rf $WORK_DIR
  mkdir -p $WORK_DIR
  cd $WORK_DIR
  cmake ../..
  make
  clang++ $CXXFLAGS -DCIFUZZ_TEST_NAME=\"$FUZZ_TEST\" -DCIFUZZ_SEED_CORPUS=\".\" -I$HOME/cifuzz/share/cifuzz/include/cifuzz -I../../modules/time_module/src -I../../modules/key_management_module/src -I../../modules/GPS_module/src -I../../modules/crypto_module/src ../../$FUZZ_TEST.cpp ../../fuzzing/StandaloneFuzzTargetMain.cpp libAUTOMOTIVE-FUZZING-EXAMPLE-CPP.a -o $FUZZ_TEST

else
  echo "Usage: $0 fuzz_test_name"
fi