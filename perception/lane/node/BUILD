load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["lane_node.cpp"],
    hdrs = ["lane_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "//perception/lane",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
