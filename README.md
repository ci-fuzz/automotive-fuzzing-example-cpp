# Description
Example for unisg libFuzzer as a library

# Build and execute
```
cifuzz run binary
cifuzz build binary
```

# Approach

This example shows how to use libFuzzer as a library, see https://llvm.org/docs/LibFuzzer.html#using-libfuzzer-as-a-library.

To use it, a few things should be done.
1. Change the compiler flag in the build settings for the executable, see [BUILD.bazel](BUILD.bazel#L33)
2. Add the appropriated linker flags, see [BUILD.bazel](BUILD.bazel#L41-L42)
3. Write a fuzz function as usual, the name of the function can be arbitrary, see [my_fuzz_test_1](my_fuzz_test_1.cpp#L5-L9)
4. Insert the function ```LLVMFuzzerRunDriver``` into the main function, see [target](target_1.cpp#L54). Alternatively, this can be executed in a separate thread, see [target](target_1.cpp#L55-L62)
5. To run and bundle this with cifuzz, the cifuzz.yaml file should be adjusted, see [cifuzz](cifuzz.yaml#L7-L12)
6. We use the build system other option for this approach. It is built using the build.sh script. This script will be executed twice, once to build the fuzzing binary and once to build the coverage binary.