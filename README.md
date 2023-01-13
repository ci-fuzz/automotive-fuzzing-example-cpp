# Description
Example for reducing the targets in the build file

# Build and execute
```
cifuzz run :my_fuzz_test_1
cifuzz run :my_fuzz_test_2
cifuzz run :another_fuzz_test
```
# Problem description

If you have a lot of fuzz targets in your bazel project, the build file can quickly become overwhelming. 

# Approaches

Whit these two approaches, a template for the fuzz target is created, into which the concrete fuzz target is passed.

## List comprehensions

Add this to BUILD.bazel
```
[cc_fuzz_test(
    name = name,
    srcs = [name+".cpp"],
    corpus = glob(
        [name+"_inputs/**"],
        allow_empty = True,
    ),
    includes = ["modules/"],
    deps = [
        "@cifuzz",
        ":AUTOMOTIVE-FUZZING-EXAMPLE-CPP"
    ]
) for name in ["my_fuzz_test_1", "my_fuzz_test_2", "another_fuzz_test"]]
```

See: https://docs.bazel.build/versions/0.18.1/skylark/spec.html#comprehensions

## Bazel macro

Create a new file 'defs.bzl' and add this into
```
load("@rules_fuzzing//fuzzing:cc_defs.bzl", "cc_fuzz_test")

def generate_fuzz_targets(names):
    for name in names:
        print("Name:" , name)
        cc_fuzz_test(
            name = name,
            srcs = [name+".cpp"],
            corpus = native.glob(
                [name+"_inputs/**"],
                allow_empty = True,
            ),
            includes = ["modules/"],
            deps = [
                "@cifuzz",
                ":AUTOMOTIVE-FUZZING-EXAMPLE-CPP"
            ]
        )
```

Add this to BUILD.bazel
```
load("//:defs.bzl", "generate_fuzz_targets")
generate_fuzz_targets(["my_fuzz_test_1", "my_fuzz_test_2", "another_fuzz_test"])
```

See: https://bazel.build/extending/macros