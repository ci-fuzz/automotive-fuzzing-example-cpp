# Description
Example for fuzzing a SUT with detached threads

# Build and execute
```
cifuzz run :simpleExample
cifuzz run :advancedExample
```
# Problem description

Note, this description is only aimed at detached threads.

The following image shows a possible example for creation and starting several threads and their sequence.
There are two ways to protect memory access:
1. Protect access by safe guards or
2. Each thread gets an exclusive memory area.

![Default sequence flow](/documentation/Default_sequence_flow.jpg)

However. let's consider what happens when this function is executed during fuzzing. The following image shows the first run. The fuzz function "LLVMFuzzerTestOneInput()" starts and invokes the function "targetFunction()". This function creates, starts detached several threads and ends, which also ends the function "LLVMFuzzerTestOneInput()". As in this example, it may be that the threads will be further executed.

![Sequence for the first run](/documentation/Fuzz_run_1.jpg)

Now, let's consider the second run, which is shown in the next image. After the function "LLVMFuzzerTestOneInput()" is finished, it is called immediately with a new fuzz date. This function involes the function "targetFunction()" and creates and starts new threads. This results in an overlap of resources, which can lead to false positive findings.

![Sequence for the second run](/documentation/Fuzz_run_2.jpg)

# Approach

In our two approaches we extend the duration of the function "LLVMFuzzerTestOneInput()".

## Simple approach

In the first example, the duration time is extended by a sleep. It is important to ensure that the value is not too large or too small. But the chosen sleep duration slows down the execution.

With this approach, nothing needs to be adjusted on the SUT. 

![Simple approach](/documentation/simpleApproach.jpg)

## Advanced approach

In this example, the detached threads will signal their finishes. Therefore, the runtime adapts dynamically. However, this requires adjustments to be made to the SUT.

![Simple approach](/documentation/advancedApproach.jpg)