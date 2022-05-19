package(default_visibility = ["//visibility:public"])

cc_library(
    name = "opencl",
    srcs = glob(["lib/libOpenCL.so*"]),
    hdrs = glob(["include/CL/**"]),
    includes = ["include"],
)

cc_library(
    name = "cuda_cudart",
    srcs = glob([
        "lib/*.so*",
        "lib/*.a",
    ]),
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    deps = [
        "@cuda_nvcc",
    ],
)
