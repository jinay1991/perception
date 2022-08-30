cc_test(
    name = "unit_tests",
    srcs = [
        "activity_message_builder_tests.cpp",
        "activity_tests.cpp",
        "data_source_mock_tests.cpp",
        "data_source_tests.cpp",
        "distraction_detector_tests.cpp",
        "distraction_message_builder_tests.cpp",
        "distraction_tests.cpp",
        "driver_camera_message_builder_tests.cpp",
        "driver_message_builder_tests.cpp",
        "driver_simulator_tests.cpp",
        "driver_tests.cpp",
        "eye_state_filter_tests.cpp",
        "fatigue_detector_tests.cpp",
        "fatigue_message_builder_tests.cpp",
        "fatigue_tests.cpp",
        "parameter_handler_mock_tests.cpp",
        "parameter_handler_tests.cpp",
        "parameters_tests.cpp",
        "perclos_tests.cpp",
        "responsiveness_message_builder_tests.cpp",
        "responsiveness_tests.cpp",
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

cc_test(
    name = "benchmark_tests",
    srcs = [
        "distraction_benchmark_tests.cpp",
        "driver_benchmark_tests.cpp",
        "fatigue_benchmark_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["benchmark"],
    deps = [
        "//perception/driver",
        "//perception/driver/datatype/test/support",
        "//perception/driver/test/support",
        "@benchmark//:benchmark_main",
    ],
)
