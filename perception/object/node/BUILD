load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["object_node.cpp"],
    hdrs = ["object_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "//perception/object",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
