#!/bin/sh
set -e

for fuzz_test_file in *fuzz*.cpp
do

    FUZZ_TEST=${fuzz_test_file%.*}
    # Create temporary working directory
    mkdir -p unpacking
    # Create bundle with cifuzz (this will only contain the libfuzzer target and no llvm_cov target)
    cifuzz bundle $FUZZ_TEST -o unpacking/$FUZZ_TEST.tar.gz

    # Build llvm_cov target
    ./fuzzing/coverage_report.sh $FUZZ_TEST

    # Change directory in work dir and unpack artifact
    cd unpacking
    tar -xvf $FUZZ_TEST.tar.gz
    rm $FUZZ_TEST.tar.gz

    # Add things to cifuzz.yaml
    if [ -d "cifuzz-corpus/$FUZZ_TEST" ]; then
      echo "      seeds: cifuzz-corpus/$FUZZ_TEST" >> cifuzz.yaml
    fi
    echo "      max_run_time: 1800" >> cifuzz.yaml
    echo "      parallel_executions: 1" >> cifuzz.yaml
    echo "    - target: $FUZZ_TEST" >> cifuzz.yaml
    echo "      engine: llvm_cov" >> cifuzz.yaml
    echo "      sanitizer: unknown_sanitizer" >> cifuzz.yaml
    echo "      build_dir: /home/dte/Documents/Intel/automotive-fuzzing-example-cpp/.cifuzz-build/llvm_cov" >> cifuzz.yaml
    echo "      path: llvm_cov/$FUZZ_TEST" >> cifuzz.yaml
    if [ -d "cifuzz-corpus/$FUZZ_TEST" ]; then
      echo "      seeds: cifuzz-corpus/$FUZZ_TEST" >> cifuzz.yaml
    fi
    echo "      max_run_time: 1800" >> cifuzz.yaml
    echo "      parallel_executions: 1" >> cifuzz.yaml

    # Add llvm build
    mkdir -p llvm_cov
    cp ../.cifuzz-build/llvm_cov/$FUZZ_TEST llvm_cov/$FUZZ_TEST

    # Add seeds
    if [ -d "cifuzz-corpus/$FUZZ_TEST" ]; then
      mkdir cifuzz-corpus
      cp -r ../.cifuzz-corpus/$FUZZ_TEST cifuzz-corpus
    fi

    # Repack everything and put it in root directory like nothing happened
    tar cfvz $FUZZ_TEST.tar.gz *
    mv $FUZZ_TEST.tar.gz ..
    cd ..
    rm -r unpacking
done
