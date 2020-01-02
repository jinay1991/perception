package(default_visibility = ["//visibility:public"])

cc_library(
    name = "caffe2",
    srcs = select({
        "@perception//bazel/platforms:macos": glob(["lib/libcaffe2_*.dylib"]),
        "//conditions:default": glob(["lib/libcaffe2_*.so"]),
    }),
)

cc_library(
    name = "c10",
    srcs = select({
        "@perception//bazel/platforms:macos": ["lib/libc10.dylib"],
        "//conditions:default": ["lib/libc10.so"],
    }),
)

cc_library(
    name = "torch",
    srcs = select({
        "@perception//bazel/platforms:macos": [
            "lib/libtorch.dylib",
        ],
        "//conditions:default": [
            "lib/libtorch.so",
            "lib/libgomp-753e6e92.so.1",
        ],
    }),
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
        ":c10",
        ":caffe2",
    ],
)
