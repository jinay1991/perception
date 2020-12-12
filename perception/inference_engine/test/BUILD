load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["inference_engine_tests.cpp"],
    data = [
        "//:testdata",
        "@ssd_mobilenet_v2_coco//:frozen_graph",
        "@ssd_mobilenet_v2_coco//:saved_model",
        "@ssd_mobilenet_v2_coco//:tflite",
        "@ssd_mobilenet_v2_coco//:torch",
    ],
    tags = ["unit"],
    deps = [
        "//perception/common",
        "//perception/inference_engine",
        "@googletest//:gtest_main",
        "@opencv",
    ],
)
