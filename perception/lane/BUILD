load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "lane",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        ":lane",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)

cc_test(
    name = "node_tests",
    srcs = ["test/lane_node_tests.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":node",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["test/lane_tests.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":lane",
        "@googletest//:gtest_main",
    ],
)
