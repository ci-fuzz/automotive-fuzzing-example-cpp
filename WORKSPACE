load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
  strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)


http_archive(
    name = "rules_fuzzing",
    sha256 = "6fd5814a271c90c196b9da723b642efb6752b2fcde137e42567a3c42a7cf9bb6",
    strip_prefix = "rules_fuzzing-949389c58e7cbbb2b3a2c7d3b840cefc3c0e6353",
    urls = ["https://github.com/CodeIntelligenceTesting/rules_fuzzing/archive/949389c58e7cbbb2b3a2c7d3b840cefc3c0e6353.tar.gz"],
)

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()

git_repository(
    name = "cifuzz",
    branch = "bazel-support",
    remote = "https://github.com/CodeIntelligenceTesting/cifuzz",
    strip_prefix = "tools/cmake/cifuzz/include/cifuzz",
)