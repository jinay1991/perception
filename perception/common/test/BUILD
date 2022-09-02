cc_test(
    name = "unit_tests",
    srcs = [
        "circular_bitset_tests.cpp",
        "current_previous_tests.cpp",
        "event_monitor_tests.cpp",
        "filter_tests.cpp",
        "finite_state_machine_tests.cpp",
        "geometry_tests.cpp",
        "logging_tests.cpp",
        "matrix_tests.cpp",
        "toggle_tests.cpp",
        "validity_range_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/common",
        "//perception/common:logging",
        "@googletest//:gtest_main",
    ],
)
