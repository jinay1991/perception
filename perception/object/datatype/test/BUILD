cc_test(
    name = "unit_tests",
    srcs = [
        # "object_tests.cpp",
        "operators_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    deps = [
        "//perception/object/datatype",
        "//perception/object/datatype/test/support",
        "@googletest//:gtest_main",
    ],
)
