load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "traffic_sign",
    srcs = [
        "traffic_sign.cpp",
    ],
    hdrs = [
        "traffic_sign.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "//perception/inference_engine",
    ],
)
