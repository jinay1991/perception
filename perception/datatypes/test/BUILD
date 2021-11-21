load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = [
        "camera_tests.cpp",
        "driver_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/datatypes",
        "@googletest//:gtest_main",
    ],
)
