load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    data = [
        "//:testdata",  # TODO: Remove
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "//perception/sensor/camera",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
