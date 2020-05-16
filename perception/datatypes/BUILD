load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "datatypes",
    srcs = [],
    hdrs = [
        "image.h",
        "inference_engine_type.h",
        "lane.h",
        "object.h",
        "traffic_light.h",
        "traffic_sign.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common/event_data_qualifier",
        "@nholthaus//:units",
        "@opencv//:core",
    ],
)
