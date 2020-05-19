load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "lane",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/sensor/camera"
    ],
)
