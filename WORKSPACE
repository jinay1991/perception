load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

new_git_repository(
    name = "googletest",
    build_file = "//bazel:gtest.BUILD",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

new_git_repository(
    name = "nholthaus",
    build_file = "//bazel:nholthaus.BUILD",
    remote = "https://github.com/nholthaus/units",
    tag = "v2.3.1",
)

new_git_repository(
    name = "nlohmann",
    build_file = "//bazel:nlohmann.BUILD",
    remote = "https://github.com/nlohmann/json",
    tag = "v3.7.0",
)

http_archive(
    name = "eigen3",
    build_file = "//bazel:eigen3.BUILD",
    strip_prefix = "eigen-eigen-323c052e1731",
    url = "https://bitbucket.org/eigen/eigen/get/3.3.7.zip",
)

new_local_repository(
    name = "uWebSockets",
    build_file = "//bazel:uWebSockets.BUILD",
    path = "/usr/",
)

http_archive(
    name = "torch",
    build_file = "//bazel:torch.BUILD",
    sha256 = "eda550df98414e4f90a854c2220da354fe50692a8e55a53e999d36dbae4cd506",
    strip_prefix = "libtorch",
    url = "https://download.pytorch.org/libtorch/cpu/libtorch-macos-1.3.1.zip",
)
