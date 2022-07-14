#!/bin/sh
set -e

# Name of fuzz test
FUZZ_TEST=$1

if test -f "$FUZZ_TEST.cpp"; then

  ./fuzzing/create_llvm_cov_target.sh $FUZZ_TEST
  
  CORPUS_DIR=.cifuzz-corpus/$FUZZ_TEST
  cd .cifuzz-build/llvm_cov
  
  # Run tests with the coverage build
  find ../../$CORPUS_DIR -type f -print0 | xargs -0 ./$FUZZ_TEST
  COVDIR=coverage
  mkdir -p $COVDIR
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