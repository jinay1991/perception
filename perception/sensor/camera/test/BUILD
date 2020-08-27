load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "node_tests",
    srcs = ["camera_node_tests.cpp"],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/camera/node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "calibration_tests.cpp",
        "camera_tests.cpp",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/camera",
        "@googletest//:gtest_main",
    ],
)
