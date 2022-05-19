package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cuda_cublas",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
)
