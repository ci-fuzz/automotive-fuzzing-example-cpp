#!/bin/sh
set -e

mkdir -p tmp
# This is a very bad hack to check if we are currently building
# the fuzzing or coverage target 
if [ "$CIFUZZ_COVERAGE_BUILD" = "1"  ]; then
    echo "Copy coverage binaries"
    cp build/${1}_coverage tmp/$1
else
    echo "Copy fuzzing binaries"
    cp build/${1}_fuzzing tmp/$1
fi