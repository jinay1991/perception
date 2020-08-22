load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["object_node_test.cpp"],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/object",
        "//perception/object/node",
        "//perception/sensor/camera/node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["object_test.cpp"],
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
