config_setting(
    name = "darwin",
    constraint_values = ["@bazel_tools//platforms:osx"],
)

cc_library(
    name = "libcaffe2",
    srcs = select({
        "darwin": glob(["lib/libcaffe2_*.dylib"]),
        "//conditions:default": glob(["lib/libcaffe2_*.so"]),
    }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libc10",
    srcs = select({
        "darwin": ["lib/libc10.dylib"],
        "//conditions:default": ["lib/libc10.so"],
    }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libtorch",
    srcs = select({
        "darwin": [
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
    visibility = ["//visibility:public"],
    deps = [
        ":libc10",
        ":libcaffe2",
    ],
)
