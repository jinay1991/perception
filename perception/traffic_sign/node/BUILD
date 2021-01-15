load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["traffic_sign_node.cpp"],
    hdrs = ["traffic_sign_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/traffic_sign",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
