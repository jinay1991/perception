cc_library(
    name = "libcaffe2",
    srcs = glob(["lib/libcaffe2_*.dylib"]),
    hdrs = glob(["include/**/*.h"]),
    copts = [
        "-std=c++11",
    ],
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libc10",
    srcs = glob(["lib/libc10_*.dylib"]),
    hdrs = glob(["include/**/*.h"]),
    copts = [
        "-std=c++11",
    ],
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libtorch",
    srcs = ["lib/libtorch.dylib"],
    hdrs = glob(["include/**/*.h"]),
    copts = [
        "-std=c++11",
    ],
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":libc10",
        ":libcaffe2",
    ],
)
