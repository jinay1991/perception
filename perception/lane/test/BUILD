load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_tests",
    srcs = glob(["*.cpp"]),
    data = [
        "//:testdata",
    ],
    tags = ["unit"],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/lane",
        "//perception/lane/node",
        "@googletest//:gtest_main",
    ],
)
