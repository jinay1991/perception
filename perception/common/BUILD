load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "common",
    hdrs = [
        "circular_bitset.h",
        "current_previous.h",
        "filter.h",
        "finite_state_machine.h",
        "logging.h",
        "toggle.h",
        "validity_range.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//perception:__subpackages__"],
    deps = [
        "@glog",
    ],
)
