load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "support",
    testonly = True,
    srcs = [],
    hdrs = [
        "operators.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//perception/traffic_sign/test:__subpackages__"],
    deps = [
        "//perception/datatypes",
    ],
)
