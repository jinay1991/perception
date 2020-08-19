load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["logging_tests.cpp"],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common/logging",
        "@googletest//:gtest_main",
    ],
)
