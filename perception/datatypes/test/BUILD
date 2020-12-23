load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["driver_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//perception/datatypes",
        "@googletest//:gtest_main",
    ],
)
