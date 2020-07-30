load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "object",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    data = [
        "@ssd_mobilenet_v2_coco//:saved_model",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
        "//perception/inference_engine",
        "//perception/sensor/camera:calibration",  # TODO: Remove this
    ],
)
