load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["traffic_sign_node_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    tags = ["component"],
    deps = [
        "//perception/traffic_sign/node",
        "//perception/traffic_sign/test/support",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "operators_tests.cpp",
        "traffic_sign_tests.cpp",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    tags = ["unit"],
    deps = [
        "//perception/traffic_sign",
        "//perception/traffic_sign/test/support",
        "@googletest//:gtest_main",
    ],
)
