load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "traffic_sign",
    srcs = [
        "traffic_sign.cpp",
    ],
    hdrs = [
        "traffic_sign.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
    ],
)
