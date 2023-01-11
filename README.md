# Description
Example for invoke origin main function from target application

# Build and execute
```
cifuzz run :my_fuzz_test_1
```
# Problem description

The default build case for a fuzzing target are depicted in the following figure. The System under Test (SUT), the fuzz function and other stuff like stubs/mocks will be compiled and linked together into a binary.

This case doesn't work if the SUT has his own main function, due to multiple definition of the main function.

![Default build case](/documentation/Fuzzing_default_build_case.jpg)

# Approach

In our approach the SUT will be seperated as a shared library and is linked to runtime into fuzz target (see BUILD.bazel). The origin main function must then still be called in the fuzz function (see my_fuzz_test_1.cpp). There are two ways to invoke the origin main function. 

1. Invoke in the same thread
```
  origin_main(1, NULL);
```
2. Or invoke in a new thread
```
  std::thread(origin_main, 1, c).detach();
```

This depends on the purpose of the main function. The following should be considered:
* initializes the main function somewhat?
* Does the main function have to run to the end?
* Does the main function call an infinite loop? 

![Build case to invoke origin main](/documentation/Fuzzing_invoke_main_build_case.jpg)