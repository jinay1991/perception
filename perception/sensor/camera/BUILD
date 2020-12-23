load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "camera",
    srcs = [
        "calibration.cpp",
        "camera.cpp",
    ],
    hdrs = [
        "calibration.h",
        "camera.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:calibration_data",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "@opencv",
    ],
)
