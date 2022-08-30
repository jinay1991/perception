cc_test(
    name = "unit_tests",
    srcs = [
        "node_mock_tests.cpp",
        "node_runner_tests.cpp",
        "node_tests.cpp",
        "null_node_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/lifecycle/test/support",
        "@googletest//:gtest_main",
    ],
)
