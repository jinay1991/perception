load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = [
        "circular_bitset_tests.cpp",
        "current_previous_tests.cpp",
        "filter_tests.cpp",
        "finite_state_machine_tests.cpp",
        "logging_tests.cpp",
        "toggle_tests.cpp",
        "validity_range_tests.cpp",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    deps = [
        "//perception/common",
        "@googletest//:gtest_main",
    ],
)
