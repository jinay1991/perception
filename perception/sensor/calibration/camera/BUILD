load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "camera",
    srcs = [
        "calibration.cpp",
    ],
    hdrs = [
        "calibration.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:calibration_data",
    ],
    visibility = ["//perception/sensor:__subpackages__"],
    deps = [
        "//perception/common",
        "@opencv",
    ],
)
