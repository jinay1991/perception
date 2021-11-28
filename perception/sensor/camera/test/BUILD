cc_test(
    name = "node_tests",
    srcs = ["camera_node_tests.cpp"],
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
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
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/camera",
        "@googletest//:gtest_main",
    ],
)
