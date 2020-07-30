load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_test",
    srcs = ["object_node_test.cpp"],
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
    name = "unit_test",
    srcs = ["object_test.cpp"],
    data = [
        "//:calibration_data",  # TODO: Remove
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
