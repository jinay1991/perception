load("//bazel/toolchains/cuda:cuda_toolchain.bzl", "cuda_toolchain")

package(default_visibility = ["//visibility:public"])

toolchain_type(
    name = "toolchain_type",
)

cuda_toolchain(
    name = "cuda_toolchain",
    nvcc = "@cuda//:nvcc",
    target_arch = "x86_64",
    tools = [
        "@cuda//:compiler_deps",
        "@cuda//:linker_deps",
    ],
    version = "11.7",
)

toolchain(
    name = "toolchain",
    toolchain = ":cuda_toolchain",
    toolchain_type = ":toolchain_type",
)
