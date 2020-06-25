load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
        "//perception/driver/common:parameters",
        "//perception/driver/degradation",
        "//perception/driver/fatigue",
        "//perception/driver/input_service",
        "//perception/driver/output_service",
        "//perception/driver/visual_attention",
    ],
)
