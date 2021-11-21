load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["traffic_sign_node_tests.cpp"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["component"],
    deps = [
        "//perception/traffic_sign/node",
        "//perception/traffic_sign/test/support",
        "@googletest//:gtest_main",
        "@middleware//:support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "operators_tests.cpp",
        "traffic_sign_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/traffic_sign",
        "//perception/traffic_sign/test/support",
        "@googletest//:gtest_main",
    ],
)
