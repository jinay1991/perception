load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "vehicle_dynamics",
    srcs = ["vehicle_dynamics.cpp"],
    hdrs = ["vehicle_dynamics.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
    ],
)
