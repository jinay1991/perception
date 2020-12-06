load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["camera_node_tests.cpp"],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = [
        "component",
        "unit",
    ],
    deps = [
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
