package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cuda_cccl",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
)
