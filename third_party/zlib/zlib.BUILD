package(default_visibility = ["//visibility:public"])

cc_library(
    name = "zlib",
    srcs = select({
        "@//bazel/platforms:macos": ["lib/libz.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libz.so"],
    }),
    hdrs = select({
        "@//bazel/platforms:macos": glob(["include/**/*.h"]),
        "//conditions:default": glob(["include/*.h"]),
    }),
    includes = select({
        "@//bazel/platforms:macos": ["include/"],
        "//conditions:default": ["include"],
    }),
)
