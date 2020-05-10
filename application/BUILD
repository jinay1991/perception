load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "perception",
    srcs = [
        "perception.cpp",
        "perception.h",
    ],
    visibility = ["//application:__subpackges__"],
    deps = [
        "//perception/common/logging",
        "//perception/simulation",
    ],
)
