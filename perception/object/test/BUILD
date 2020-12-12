load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["object_node_tests.cpp"],
    tags = [
        "component",
        "unit",
    ],
    deps = [
        "//perception/datatypes",
        "//perception/object/node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["object_tests.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
