load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["object_node_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
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
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
