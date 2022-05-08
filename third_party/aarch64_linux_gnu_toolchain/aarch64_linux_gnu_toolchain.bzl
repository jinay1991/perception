load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def aarch64_linux_gnu_toolchain():
    maybe(
        http_archive,
        name = "aarch64_linux_gnu_toolchain",
        url = "https://snapshots.linaro.org/gnu-toolchain/12.0-2022.02-1/aarch64-linux-gnu/gcc-linaro-12.0.1-2022.02-x86_64_aarch64-linux-gnu.tar.xz",
        sha256 = "1657c086d20fd9fba7572540a4be2c4b566273704ee2fb2e3c2e709187eceef1",
        strip_prefix = "gcc-linaro-12.0.1-2022.02-x86_64_aarch64-linux-gnu",
        build_file = "//third_party/aarch64_linux_gnu_toolchain:aarch64_linux_gnu_toolchain.BUILD",
    )
