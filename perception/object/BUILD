load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

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
        "@opencv",
    ],
)

cc_library(
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":object",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)

cc_test(
    name = "node_tests",
    srcs = ["test/object_node_tests.cpp"],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":node",
        "//perception/sensor/camera:node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["test/object_tests.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":object",
        "@googletest//:gtest_main",
    ],
)
