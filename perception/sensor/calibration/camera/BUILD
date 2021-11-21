load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "camera",
    srcs = [
        "calibration.cpp",
    ],
    hdrs = [
        "calibration.h",
    ],
    data = [
        "//:calibration_data",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/sensor:__subpackages__"],
    deps = [
        "//perception/common",
        "@opencv",
    ],
)
