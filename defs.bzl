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