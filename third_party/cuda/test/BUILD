cc_test(
    name = "unit_tests",
    srcs = [
        "cuda_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "@cuda",
        "@googletest//:gtest_main",
    ],
)
