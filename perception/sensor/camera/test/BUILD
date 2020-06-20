load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "unit_test",
    srcs = glob(["*.cpp"]),
    data = [
        "//:calibration_data",
        "//:testdata",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/communication:topics",
        "//perception/sensor/camera",
        "//perception/sensor/camera/node",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)
