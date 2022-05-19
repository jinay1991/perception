package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cuda_nvcc",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
)

filegroup(
    name = "bin",
    srcs = ["bin/nvcc"],
)

filegroup(
    name = "compiler_pieces",
    srcs = glob([
        "bin/**",
        "lib/**",
    ]),
)
