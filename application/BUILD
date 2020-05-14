load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "perception",
    srcs = [
        "main.cpp",
        "perception.cpp",
        "perception.h",
    ],
    visibility = ["//application:__subpackages__"],
    deps = [
        "//perception/common/logging",
        "//perception/simulation",
    ],
)
