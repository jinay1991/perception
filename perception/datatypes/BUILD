load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "datatypes",
    srcs = [],
    hdrs = [
        "camera.h",
        "driver.h",
        "inference_engine_type.h",
        "lane.h",
        "object.h",
        "traffic_light.h",
        "traffic_sign.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@nholthaus//:units",
        "@opencv//:core",
    ],
)
