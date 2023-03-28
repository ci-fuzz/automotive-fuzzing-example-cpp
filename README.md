# Description
Example for fuzzing a SUT which throws a signal.

# Build and execute
```
cifuzz run :my_fuzz_test
cifuzz run :approach1
cifuzz run :approach2
cifuzz run :approach3
cifuzz run :approachDNW4
cifuzz run :approachDNW5
```
# Problem description

If a SUT uses signals for termination of the execution it makes it more difficult to fuzz them. Because when a signal is triggered, the fuzz is also terminated.

To demonstrate this run:
```
cifuzz run :my_fuzz_test
```

It is also possible to ignor the signal, but this will cause the application to continue. 
For demonstrate run this:
```
ASAN_OPTIONS=halt_on_error=0 cifuzz run :my_fuzz_test -v --engine-arg -handle_abrt=0
```
For more information about Sanitizer flags consider https://github.com/google/sanitizers/wiki/SanitizerCommonFlags

# Approaches

These three approaches show how to handle this.

## Approach 1 fork the SUT
With this approach the SUT is executed in a separate process. So that the further execution is stopped. But each signal is considered as a finding. To prevent this, a own signal handler can be used, as in this example.
The SUT does not need to be change for this.

```
cifuzz run :approach1
```

**NOTE:**
However, the main disadvantage of this approach is that the fuss tests be carried out very slowly.

## Approach 2 load execution context 
In the next approach the execution context are saved and reloaded if the programme is to prevent further execution. For this, the std::rais() function is mocked at the linking time and instead of triggering a signal, a previously defined context is loaded.
The SUT does not need to be change for this.

```
cifuzz run :approach2
```

## Approach 3 thow exception 
This approach shows how to throw an exception to prevent further execution. An additional obstacle is that no exceptions can be thrown in the function. For this, the std::rais() function is mocked at the linking time and instead of triggering a signal, a exception is throwing.
The SUT is slightly modified for this purpose. A corresponding value is passed to the noexpect().

```
cifuzz run :approach3
```

## Approach 4 Does Not Work load execution context 
In the next approach the execution context are saved and reloaded if the programme is to prevent further execution. For this, an own signal handler is created intercept a abort signal and load the context.
But this approach does not work!

```
cifuzz run :approachDNW4
```

## Approach 5 Does Not Work thow exception 
This approach shows how to throw an exception to prevent further execution. For this, an own signal handler is created intercept a abort signal and load the context.
But this approach does not work!
The SUT is slightly modified for this purpose. A corresponding value is passed to the noexpect().

```
cifuzz run :approachDNW5
```