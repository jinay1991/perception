cc_test(
    name = "unit_tests",
    srcs = ["object_tests.cpp"],
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["unit"],
    deps = [
        "//perception/object",
        "@googletest//:gtest_main",
    ],
)
