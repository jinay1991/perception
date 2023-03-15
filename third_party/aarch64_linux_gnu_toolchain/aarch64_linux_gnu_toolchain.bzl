load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def aarch64_linux_gnu_toolchain():
    maybe(
        http_archive,
        name = "aarch64_linux_gnu_toolchain",
        url = "https://snapshots.linaro.org/gnu-toolchain/12.1-2023.08-1/aarch64-linux-gnu/gcc-linaro-12.1.1-2023.08-x86_64_aarch64-linux-gnu.tar.xz",
        sha256 = "18a961a7ade3f09b23ea6f05a3a923595c8abf3761a66161d39f583a495e21d8",
        strip_prefix = "gcc-linaro-12.1.1-2023.08-x86_64_aarch64-linux-gnu",
        build_file = "//third_party/aarch64_linux_gnu_toolchain:aarch64_linux_gnu_toolchain.BUILD",
    )
