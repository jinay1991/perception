load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "unit_test",
    srcs = glob(["*.cpp"]),
    data = [
        "//:testdata",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/sensor/camera",
        "@googletest//:gtest_main",
    ],
)
