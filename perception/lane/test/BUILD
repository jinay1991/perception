load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["lane_node_tests.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/lane",
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
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/lane",
        "//perception/lane/node",
        "@googletest//:gtest_main",
    ],
)
