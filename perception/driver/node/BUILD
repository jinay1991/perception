load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["driver_node.cpp"],
    hdrs = ["driver_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/driver",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
