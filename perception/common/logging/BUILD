load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "logging",
    srcs = ["logging.cpp"],
    hdrs = ["logging.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "unit_tests",
    srcs = ["test/logging_tests.cpp"],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":logging",
        "@googletest//:gtest_main",
    ],
)
