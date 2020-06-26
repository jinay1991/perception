load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_test",
    srcs = glob(["*.cpp"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/object",
        "//perception/object/node",
        "//perception/sensor/camera/node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)
