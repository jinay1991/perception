load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

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
