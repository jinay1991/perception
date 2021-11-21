load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["object_node_tests.cpp"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = [
        "component",
    ],
    deps = [
        "//perception/datatypes",
        "//perception/object/node",
        "@googletest//:gtest_main",
        "@middleware//:support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["object_tests.cpp"],
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
