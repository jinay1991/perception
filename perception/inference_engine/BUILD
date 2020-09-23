load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "inference_engine",
    srcs = [
        "inference_engine_strategy.cpp",
        "null_inference_engine.cpp",
        "opencv_inference_engine.cpp",
        "tf_inference_engine.cpp",
        "tflite_inference_engine.cpp",
        "torch_inference_engine.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "inference_engine_strategy.h",
        "null_inference_engine.h",
        "opencv_inference_engine.h",
        "tf_inference_engine.h",
        "tflite_inference_engine.h",
        "torch_inference_engine.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        "@opencv//:dnn",
        "@tensorflow",
        "@tensorflowlite",
        "@torch",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["test/inference_engine_tests.cpp"],
    data = [
        "//:testdata",
        "@ssd_mobilenet_v2_coco//:frozen_graph",
        "@ssd_mobilenet_v2_coco//:saved_model",
        "@ssd_mobilenet_v2_coco//:tflite",
    ],
    linkstatic = True,
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":inference_engine",
        "//perception/common/logging",
        "@googletest//:gtest_main",
        "@opencv",
    ],
)
