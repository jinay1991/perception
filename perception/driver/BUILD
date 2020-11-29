load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "driver",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
    ],
)

cc_library(
    name = "support",
    testonly = True,
    srcs = glob(["test/support/**/*.cpp"]),
    hdrs = glob(["test/support/**/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
    ],
)

cc_library(
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        ":driver",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = glob(["test/*.cpp"]),
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":driver",
        ":support",
        "@googletest//:gtest_main",
    ],
)
