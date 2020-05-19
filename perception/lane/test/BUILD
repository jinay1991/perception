load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unit_test",
    srcs = glob(["*.cpp"]),
    data = [
        "//:testdata",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/lane",
        "@googletest//:gtest_main",
    ],
)
