package(default_visibility = ["//visibility:public"])

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
