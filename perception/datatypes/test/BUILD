load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "message_builders",
    hdrs = [
        "camera_message_builder.h",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = ["//perception/datatypes"],
)
