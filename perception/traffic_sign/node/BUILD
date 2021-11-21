load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["traffic_sign_node.cpp"],
    hdrs = ["traffic_sign_node.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/traffic_sign",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
