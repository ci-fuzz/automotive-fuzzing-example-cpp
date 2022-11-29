load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
  strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)


http_archive(
    name = "rules_fuzzing",
    sha256 = "4beab98d88e4bf2d04da0412d413a1364f95e5eb88963e15e603bee1410fcedf",
    strip_prefix = "rules_fuzzing-ca617e846d0f92e00a903903b0554ea9142e1132",
    urls = ["https://github.com/CodeIntelligenceTesting/rules_fuzzing/archive/ca617e846d0f92e00a903903b0554ea9142e1132.tar.gz"],
)

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()

git_repository(
    name = "cifuzz",
    commit = "1ccb0bb7f27864626f668cca6d6e87776e6f87bd",
    remote = "https://github.com/CodeIntelligenceTesting/cifuzz-bazel",
)