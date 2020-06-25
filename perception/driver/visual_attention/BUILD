load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "visual_attention",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/driver/common:parameters",
    ],
)
