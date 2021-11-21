load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["calibration_tests.cpp"],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/calibration/camera",
        "@googletest//:gtest_main",
    ],
)
