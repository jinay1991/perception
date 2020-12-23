load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["lane_node_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
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
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/lane",
        "@googletest//:gtest_main",
    ],
)
