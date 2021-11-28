cc_test(
    name = "node_tests",
    srcs = ["lane_node_tests.cpp"],
    data = [
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
        "//perception/lane/node",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["lane_tests.cpp"],
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/lane",
        "@googletest//:gtest_main",
    ],
)
