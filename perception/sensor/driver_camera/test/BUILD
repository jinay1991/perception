load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["driver_camera_tests.cpp"],
    data = ["//:testdata"],
    deps = [
        "//perception/sensor/driver_camera",
        "@googletest//:gtest_main",
    ],
)
