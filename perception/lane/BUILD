load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "lane",
    srcs = ["lane.cpp"],
    hdrs = ["lane.h"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
        "@opencv",
    ],
)
