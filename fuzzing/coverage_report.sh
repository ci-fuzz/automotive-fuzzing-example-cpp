#!/bin/sh
set -e

# Name of fuzz test
FUZZ_TEST=$1

if test -f "$FUZZ_TEST.cpp"; then

  CORPUS_DIR=.cifuzz-corpus/$FUZZ_TEST

  # Build target to measure coverage
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
  clang++ $CXXFLAGS -DCIFUZZ_TEST_NAME=\"$FUZZ_TEST\" -DCIFUZZ_SEED_CORPUS=\".\" -I/home/dte/cifuzz/share/cifuzz/include/cifuzz -I../../modules/time_module/src -I../../modules/key_management_module/src -I../../modules/GPS_module/src -I../../modules/crypto_module/src ../../$FUZZ_TEST.cpp ../../fuzzing/StandaloneFuzzTargetMain.cpp libAUTOMOTIVE-FUZZING-EXAMPLE-CPP.a -o $FUZZ_TEST

  # Run tests with the coverage build
  echo "$CORPUS_DIR"
  find ../../$CORPUS_DIR -type f -print0 | xargs -0 ./$FUZZ_TEST
  COVDIR=coverage
  mkdir $COVDIR
  mv default.profraw "$COVDIR"

  # Convert raw coverage data
  llvm-profdata merge -sparse "$COVDIR/default.profraw" -o "$COVDIR/default.profdata"

  # Generate a text report (summary)
  llvm-cov report $FUZZ_TEST -instr-profile="$COVDIR/default.profdata" > "$COVDIR/coverage_llvm.txt"

  # Generate an html report
  llvm-cov show $FUZZ_TEST -instr-profile="$COVDIR/default.profdata" --format=html > "$COVDIR/source_coverage.html"

  # Generate an lcov report
  llvm-cov export --format=lcov -instr-profile="$COVDIR/default.profdata" $FUZZ_TEST > "$COVDIR/coverage.lcov"
  # The symlink is picked up by the VSCode "Coverage Gutters" extension
  cp "$COVDIR/coverage.lcov" ../../lcov.info
else
  echo "Usage: $0 fuzz_test_name"
fi