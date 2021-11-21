load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["camera_node.cpp"],
    hdrs = ["camera_node.h"],
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/camera",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
