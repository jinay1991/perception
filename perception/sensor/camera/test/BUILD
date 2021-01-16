load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["camera_node_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    tags = [
        "component",
    ],
    deps = [
        "//perception/sensor/camera/node",
        "@googletest//:gtest_main",
        "@middleware//:support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "camera_tests.cpp",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/camera",
        "@googletest//:gtest_main",
    ],
)
