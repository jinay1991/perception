load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "//perception/object",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
