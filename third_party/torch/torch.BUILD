package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libcaffe2",
    srcs = glob(["lib/libcaffe2_*.dylib"]),
)

cc_library(
    name = "libc10",
    srcs = ["lib/libc10.dylib"],
)

cc_library(
    name = "libtorch",
    srcs = ["lib/libtorch.dylib"],
    hdrs = glob(["include/**/*.h"]),
    copts = [
        "-std=c++11",
        "-D_GLIBCXX_USE_CXX11_ABI=0",
    ],
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
    deps = [
        ":libc10",
        ":libcaffe2",
    ],
)
