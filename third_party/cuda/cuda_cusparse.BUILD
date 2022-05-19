package(default_visibility = ["//visibility:public"])

cc_library(
    name = "cuda_cusparse",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
)
