load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "calibration",
    srcs = ["calibration.cpp"],
    hdrs = ["calibration.h"],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        "@opencv",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cpp"],
    hdrs = ["camera.h"],
    data = [
        "//:calibration_data",
    ],
    deps = [
        ":calibration",
        "//perception/common/logging",
        "//perception/datatypes",
        "@middleware//middleware/lifecycle",
        "@opencv",
    ],
)
