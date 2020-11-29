load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "common",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
)

cc_test(
    name = "unit_tests",
    srcs = glob(["test/*.cpp"]),
    visibility = ["//visibility:public"],
    deps = [
        ":common",
        "@googletest//:gtest_main",
    ],
)
