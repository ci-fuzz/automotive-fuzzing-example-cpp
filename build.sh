#!/bin/sh
set -e

mkdir -p tmp
# This is a very bad hack to check if we are currently building
# the fuzzing or coverage target 
if [ "$CIFUZZ_COVERAGE_BUILD" = "1"  ]; then
    echo "Build coverage binaries"
    bazel build :${1}_coverage 
    echo "Copy coverage binaries"
    cp bazel-bin/${1}_coverage tmp/$1
else
    echo "Build fuzzing binaries"
    bazel build :${1}_fuzzing
    echo "Copy fuzzing binaries"
    cp bazel-bin/${1}_fuzzing tmp/$1
fi