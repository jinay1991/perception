package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libuv",
    srcs = select({
        "@perception//bazel/platforms:macos": ["local/lib/libuv.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libuv.so"],
    }),
    hdrs = select({
        "@perception//bazel/platforms:macos": glob(["local/include/**/*.h"]),
        "//conditions:default": glob(["include/**/*.h"]),
    }),
    includes = select({
        "@perception//bazel/platforms:macos": ["local/include/"],
        "//conditions:default": ["include"],
    }),
)

cc_library(
    name = "libz",
    srcs = select({
        "@perception//bazel/platforms:macos": ["lib/libz.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libz.so"],
    }),
    hdrs = select({
        "@perception//bazel/platforms:macos": glob(["include/**/*.h"]),
        "//conditions:default": glob(["include/*.h"]),
    }),
    includes = select({
        "@perception//bazel/platforms:macos": ["include/"],
        "//conditions:default": ["include"],
    }),
)

cc_library(
    name = "libssl",
    srcs = select({
        "@perception//bazel/platforms:macos": ["local/opt/openssl/lib/libssl.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libssl.so"],
    }),
    hdrs = select({
        "@perception//bazel/platforms:macos": glob(["local/opt/openssl/include/**/*.h"]),
        "//conditions:default": glob(["include/openssl/*.h"]),
    }),
    includes = select({
        "@perception//bazel/platforms:macos": ["local/opt/openssl/include"],
        "//conditions:default": ["include"],
    }),
)

cc_library(
    name = "libuWS",
    srcs = select({
        "@perception//bazel/platforms:macos": ["local/lib/libuWS.dylib"],
        "//conditions:default": ["lib/libuWS.so"],
    }),
    includes = select({
        "@perception//bazel/platforms:macos": ["local/include"],
        "//conditions:default": ["include"],
    }),
    deps = [
        ":libssl",
        ":libuv",
        ":libz",
    ],
)
