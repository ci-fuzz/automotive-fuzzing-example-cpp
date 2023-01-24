# Description
Example for fuzzing a SUT with throws a signal.

# Build and execute
```
cifuzz run :my_fuzz_test_1
cifuzz run :my_fuzz_test_2
cifuzz run :my_fuzz_test_3
```
# Problem description

If a SUT uses signals for termination of the execution it makes it more difficult to fuzz them. Because when a signal is triggered, the fuzz is also terminated.

To demonstrate this run:
```
cifuzz run :my_fuzz_test_1
```


# Approaches

These two approaches show how to handle this.

## Mock the triggering function
With this approach the function, which causes the signal will be mocked. So that signal does not be triggered.

```
cifuzz run :my_fuzz_test_2
```

Function will be mocked at linking time. A certain mock function must be present. To do this, 

1. find the function to mock in the binaries.
For example with:
```
nm binary | grep parser

000000000010d200 T __wrap__Z6parserh
000000000010dd50 T _Z6parserh
```
The output may look like this: "_Z6parserh". The wrap function name must be created with the prefix "__wrap" concaninate with the symbol name "_Z6parserh".

---
**NOTE:**
The symbol name depends on compiler and architecture
---

2. Add this link option into the fuzztarget
```
linkopts = ["-Wl,--wrap=_Z6parserh"]
```

3. Write the mock function into the fuzztarget

```
extern "C" uint8_t __wrap__Z6parserh(){
    return 0;
}
```

4. Build and run!

---
**NOTE:**

The disadvantage of this approach is that all functions that trigger a signal have to be mocked and that the original functions are not covered by fuzzing.

---


## Own signal handler
The next approach uses the possibility that some signals can be intercepted.

```
cifuzz run :my_fuzz_test_3
```

These signals are affected:

* SIGABRT
* SIGFPE
* SIGILL
* SIGINT
* SIGSEGV
* SIGTERM

To intercept these, write a signal handler and pass it to signal.

These signals can be intercept in the whole binary. But the disadvantage is to chose careful the signals to be intercepted because libFuzzer react also on certain signals like SIGSEGV