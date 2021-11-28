cc_test(
    name = "unit_tests",
    srcs = [
        "linear_kalman_filter_tests.cpp",
        "multivariate_moments_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/common/kalman_filter",
        "@googletest//:gtest_main",
    ],
)
