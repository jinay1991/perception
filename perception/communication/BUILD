load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "topics",
    hdrs = ["topics.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@middleware//:communication",
    ],
)
