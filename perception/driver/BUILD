load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
    ],
)
