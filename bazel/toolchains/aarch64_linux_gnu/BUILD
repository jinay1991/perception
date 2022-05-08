load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")
load(":aarch64_linux_gnu_toolchain_config.bzl", "aarch64_linux_gnu_toolchain_config")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "empty",
    srcs = [],
)

filegroup(
    name = "linker_files",
    srcs = [
        "//bazel/toolchains/aarch64_linux_gnu/bin:ar",
        "//bazel/toolchains/aarch64_linux_gnu/bin:lcov",
        "//bazel/toolchains/aarch64_linux_gnu/bin:ld",
        "@aarch64_linux_gnu_toolchain//:compiler_pieces",
    ],
)

filegroup(
    name = "compiler_files",
    srcs = [
        "//bazel/toolchains/aarch64_linux_gnu/bin:ar",
        "//bazel/toolchains/aarch64_linux_gnu/bin:cpp",
        "//bazel/toolchains/aarch64_linux_gnu/bin:dwp",
        "//bazel/toolchains/aarch64_linux_gnu/bin:g++",
        "//bazel/toolchains/aarch64_linux_gnu/bin:gcc",
        "//bazel/toolchains/aarch64_linux_gnu/bin:lcov",
        "//bazel/toolchains/aarch64_linux_gnu/bin:nm",
        "@aarch64_linux_gnu_toolchain//:compiler_pieces",
    ],
)

filegroup(
    name = "all_files",
    srcs = [
        ":compiler_files",
        ":linker_files",
    ],
)

aarch64_linux_gnu_toolchain_config(name = "toolchain_config")

cc_toolchain(
    name = "toolchain",
    all_files = ":all_files",
    ar_files = ":compiler_files",
    compiler_files = ":compiler_files",
    dwp_files = ":compiler_files",
    linker_files = ":compiler_files",
    objcopy_files = ":compiler_files",
    strip_files = ":compiler_files",
    supports_param_files = 1,
    toolchain_config = ":toolchain_config",
    toolchain_identifier = "aarch64-linux-gnu",
)

cc_toolchain_suite(
    name = "toolchain_suite",
    tags = ["manual"],
    toolchains = {
        "aarch64|gcc": "//bazel/toolchains/aarch64_linux_gnu:toolchain",
    },
)
