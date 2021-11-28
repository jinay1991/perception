cc_test(
    name = "unit_tests",
    srcs = ["driver_camera_tests.cpp"],
    data = [
        "//:testdata",
        "@opencv//data:all_images",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/sensor/driver_camera",
        "@googletest//:gtest_main",
    ],
)
