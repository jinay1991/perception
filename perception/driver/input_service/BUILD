load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "input_service",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
        "//perception/driver/common:parameters",
    ],
)
