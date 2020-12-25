load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "common",
    hdrs = [
        "circular_bitset.h",
        "current_previous.h",
        "filter.h",
        "logging.h",
        "validity_range.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
    ],
)
