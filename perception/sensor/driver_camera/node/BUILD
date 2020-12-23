load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["driver_camera_node.cpp"],
    hdrs = ["driver_camera_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/driver_camera",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
