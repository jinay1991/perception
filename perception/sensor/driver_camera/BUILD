load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver_camera",
    srcs = [
        "driver_camera.cpp",
    ],
    hdrs = [
        "driver_camera.h",
    ],
    data = ["@opencv//:haarcascades"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "@opencv",
    ],
)
