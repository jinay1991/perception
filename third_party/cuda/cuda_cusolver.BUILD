package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cuda_cusolver",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
)
