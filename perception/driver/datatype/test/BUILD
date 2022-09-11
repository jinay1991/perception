cc_test(
    name = "unit_tests",
    srcs = [
        "driver_camera_message_tests.cpp",
        "driver_message_tests.cpp",
        "driver_tests.cpp",
        "operators_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/driver/datatype",
        "//perception/driver/datatype/test/support",
        "@googletest//:gtest_main",
    ],
)
