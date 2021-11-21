load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "support",
    testonly = True,
    srcs = [],
    hdrs = [
        "operators.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/traffic_sign/test:__subpackages__"],
    deps = [
        "//perception/datatypes",
    ],
)
