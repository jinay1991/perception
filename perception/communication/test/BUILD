cc_test(
    name = "unit_tests",
    srcs = [
        "message_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication",
        "@googletest//:gtest_main",
    ],
)
