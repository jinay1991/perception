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
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        ":driver",
        "//perception/communication:topics",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)

cc_library(
    name = "support",
    testonly = True,
    srcs = glob(["test/support/**/*.cpp"]),
    hdrs = glob(["test/support/**/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "node_tests",
    srcs = ["test/driver_node_tests.cpp"],
    tags = [
        "component",
        "unit",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":node",
        ":support",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "test/data_source_tests.cpp",
        "test/driver_camera_message_builder_tests.cpp",
        "test/driver_consumer_node_tests.cpp",
        "test/driver_simulator_node_tests.cpp",
        "test/driver_tests.cpp",
        "test/fatigue_tests.cpp",
        "test/operators_tests.cpp",
        "test/parameter_handler_tests.cpp",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        ":driver",
        ":support",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "benchmark_tests",
    srcs = [
        "test/driver_benchmark_tests.cpp",
    ],
    tags = [
        "benchmark",
        "manual",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":node",
        ":support",
        "@benchmark//:benchmark_main",
    ],
)
