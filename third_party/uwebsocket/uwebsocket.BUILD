package(default_visibility = ["//visibility:public"])

cc_library(
    name = "uwebsocket",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["src/*.h"]),
    copts = [
        "-std=c++11",
    ],
    includes = ["src"],
    linkopts = [
        "-lpthread",
    ],
    deps = [
        "@libuv",
        "@openssl//:libssl",
        "@zlib",
    ],
)
