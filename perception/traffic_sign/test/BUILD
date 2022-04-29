cc_test(
    name = "unit_tests",
    srcs = [
        "operators_tests.cpp",
        "traffic_sign_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/traffic_sign",
        "//perception/traffic_sign/test/support",
        "@googletest//:gtest_main",
    ],
)
