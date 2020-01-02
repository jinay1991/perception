package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libuv",
    srcs = select({
        "@//bazel/platforms:macos": ["local/lib/libuv.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libuv.so"],
    }),
    hdrs = select({
        "@//bazel/platforms:macos": glob(["local/include/**/*.h"]),
        "//conditions:default": glob(["include/**/*.h"]),
    }),
    includes = select({
        "@//bazel/platforms:macos": ["local/include/"],
        "//conditions:default": ["include"],
    }),
)
