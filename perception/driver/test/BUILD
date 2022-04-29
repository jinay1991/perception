cc_test(
    name = "unit_tests",
    srcs = [
        "data_source_mock_tests.cpp",
        "data_source_tests.cpp",
        "driver_camera_message_builder_tests.cpp",
        "driver_tests.cpp",
        "eye_state_filter_tests.cpp",
        "fatigue_message_builder_tests.cpp",
        "fatigue_tests.cpp",
        "operators_tests.cpp",
        "parameter_handler_mock_tests.cpp",
        "parameter_handler_tests.cpp",
        "parameters_tests.cpp",
        "perclos_tests.cpp",
        "visual_attention_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/driver",
        "//perception/driver/test/support",
        "@googletest//:gtest_main",
    ],
)
