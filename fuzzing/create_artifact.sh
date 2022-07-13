#!/bin/sh
set -e

# Name of fuzz test
FUZZ_TEST=$1

if test -f "$FUZZ_TEST.cpp"; then
    # Create temporary working directory
    mkdir unpacking
    # Create bundle with cifuzz (this will only contain the libfuzzer target and no llvm_cov target)
    cifuzz bundle $FUZZ_TEST -o unpacking/$FUZZ_TEST.tar.gz

    # Change directory in work dir and unpack artifact
    cd unpacking
    tar -xvf $FUZZ_TEST.tar.gz
    rm $FUZZ_TEST.tar.gz

    # Add things to cifuzz.yaml
    echo "      seeds: cifuzz-corpus/$FUZZ_TEST" >> cifuzz.yaml
    echo "      max_run_time: 1800" >> cifuzz.yaml
    echo "      parallel_executions: 1" >> cifuzz.yaml
    echo "    - target: $FUZZ_TEST" >> cifuzz.yaml
    echo "      engine: llvm_cov" >> cifuzz.yaml
    echo "      sanitizer: unknown_sanitizer" >> cifuzz.yaml
    echo "      build_dir: /home/dte/Documents/Intel/automotive-fuzzing-example-cpp/.cifuzz-build/llvm_cov" >> cifuzz.yaml
    echo "      path: llvm_cov/$FUZZ_TEST" >> cifuzz.yaml
    echo "      seeds: cifuzz-corpus/$FUZZ_TEST" >> cifuzz.yaml
    echo "      max_run_time: 1800" >> cifuzz.yaml
    echo "      parallel_executions: 1" >> cifuzz.yaml

    # Add llvm build
    mkdir -p llvm_cov
    cp ../.cifuzz-build/llvm_cov/$FUZZ_TEST llvm_cov/$FUZZ_TEST

    # Add seeds
    mkdir cifuzz-corpus
    cp -r ../.cifuzz-corpus/$FUZZ_TEST cifuzz-corpus

    # Repack everything and put it in root directory like nothing happened
    tar cfvz $FUZZ_TEST.tar.gz *
    mv $FUZZ_TEST.tar.gz ..
    cd ..
    rm -r unpacking
else
  echo "Usage: $0 fuzz_test_name"
fi
