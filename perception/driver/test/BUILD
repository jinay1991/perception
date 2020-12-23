load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "node_tests",
    srcs = ["driver_node_tests.cpp"],
    copts = [
        "-Wall",
        "-Werror",
    ],
    tags = ["component"],
    deps = [
        "//perception/driver/node",
        "//perception/driver/test/support",
        "@googletest//:gtest_main",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = [
        "data_source_tests.cpp",
        "driver_camera_message_builder_tests.cpp",
        "driver_consumer_node_tests.cpp",
        "driver_simulator_node_tests.cpp",
        "driver_tests.cpp",
        "fatigue_message_builder_tests.cpp",
        "fatigue_tests.cpp",
        "operators_tests.cpp",
        "parameter_handler_tests.cpp",
        "parameters_tests.cpp",
        "perclos_tests.cpp",
        "visual_attention_tests.cpp",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    tags = ["unit"],
    deps = [
        "//perception/driver",
        "//perception/driver/test/support",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "benchmark_tests",
    srcs = [
        "driver_benchmark_tests.cpp",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    tags = ["benchmark"],
    deps = [
        "//perception/driver/node",
        "//perception/driver/test/support",
        "@benchmark//:benchmark_main",
    ],
)
