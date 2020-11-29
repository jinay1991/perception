load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "calibration",
    srcs = ["calibration.cpp"],
    hdrs = ["calibration.h"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "@opencv",
    ],
)

cc_library(
    name = "camera",
    srcs = ["camera.cpp"],
    hdrs = ["camera.h"],
    data = [
        "//:calibration_data",
    ],
    deps = [
        ":calibration",
        "//perception/common",
        "//perception/datatypes",
        "@middleware//middleware/lifecycle",
        "@opencv",
    ],
)

cc_library(
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    data = [
        "//:testdata",  # TODO: Remove
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":camera",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)

cc_test(
    name = "node_tests",
    srcs = ["test/camera_node_tests.cpp"],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        ":node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "test/calibration_tests.cpp",
        "test/camera_tests.cpp",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        ":camera",
        "@googletest//:gtest_main",
    ],
)
