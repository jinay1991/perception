package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libssl",
    srcs = select({
        "@platforms/os:macos": ["local/opt/openssl/lib/libssl.dylib"],
        "//conditions:default": ["lib/x86_64-linux-gnu/libssl.so"],
    }),
    hdrs = select({
        "@platforms/os:macos": glob(["local/opt/openssl/include/**/*.h"]),
        "//conditions:default": glob(["include/openssl/*.h"]),
    }),
    includes = select({
        "@platforms/os:macos": ["local/opt/openssl/include"],
        "//conditions:default": ["include"],
    }),
)
