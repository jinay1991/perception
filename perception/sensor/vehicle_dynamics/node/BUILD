load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["vehicle_dynamics_node.cpp"],
    hdrs = ["vehicle_dynamics_node.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/vehicle_dynamics",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
