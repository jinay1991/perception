load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_test",
    srcs = ["inference_engine_tests.cpp"],
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common/logging",
        "//perception/inference_engine",
        "@googletest//:gtest_main",
        "@opencv",
    ],
)
