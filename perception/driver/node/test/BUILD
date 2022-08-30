cc_test(
    name = "unit_tests",
    srcs = [
        "driver_node_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/driver/node",
        "@googletest//:gtest_main",
    ],
)
