load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "node_tests",
    srcs = ["vehicle_dynamics_node_tests.cpp"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = [
        "component",
    ],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/vehicle_dynamics/node",
        "@googletest//:gtest_main",
        "@middleware//:support",
    ],
)

cc_test(
    name = "unit_tests",
    srcs = ["vehicle_dynamics_tests.cpp"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/sensor/vehicle_dynamics",
        "@googletest//:gtest_main",
    ],
)
