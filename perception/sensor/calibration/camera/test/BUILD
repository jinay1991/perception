load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["calibration_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/calibration/camera",
        "@googletest//:gtest_main",
    ],
)
