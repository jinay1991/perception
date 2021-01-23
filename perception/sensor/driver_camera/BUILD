load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver_camera",
    srcs = [
        "driver_camera.cpp",
    ],
    hdrs = [
        "driver_camera.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "@opencv//:haarcascades",
        "@opencv//:lbpcascades",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "@opencv",
    ],
)
