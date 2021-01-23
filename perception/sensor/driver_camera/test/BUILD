load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = ["driver_camera_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    data = [
        "//:testdata",
        "@opencv//data:all_images",
    ],
    deps = [
        "//perception/sensor/driver_camera",
        "@googletest//:gtest_main",
    ],
)
