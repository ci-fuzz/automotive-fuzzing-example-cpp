#!/bin/bash
if [ $# -ne 1 ]
  then
    echo "Usage: $0 {run, coverage, bundle}"
    exit 1
fi

if [ "$1" == "run" ]; then
  cmake -S . --preset=cifuzz_run
  cifuzz run --build-command="cmake --build --preset=build_cifuzz_run --target my_fuzz_test_1" out/build/cifuzz_run/my_fuzz_test_1
  cmake -S . --preset=cifuzz_coverage
elif [ "$1" == "coverage" ]; then
  # We have to specify the following:
  # build_command: How to build the coverage target (e.g. select coverage preset)
  # seed-corpus: If the coverage target will be build in a different folder than the run target we need to specify this to point to the correct corpus dir
  # path to coverage binary (when it is build)
  cifuzz coverage --build-command="cmake --build --preset=build_cifuzz_coverage --target my_fuzz_test_1" --seed-corpus=".cifuzz-corpus/out/build/cifuzz_run" out/build/cifuzz_coverage/my_fuzz_test_1 --format lcov -o lcov.info
elif [ "$1" == "bundle" ]; then
  cifuzz bundle --build-command=./build_bundle.sh out/build/cifuzz_bundle/my_fuzz_test_1
else
  echo "Usage: $0 {run, coverage, bundle}"
fi

