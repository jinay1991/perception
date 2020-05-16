load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "camera",
    srcs = [
        "calibration.cpp",
        "camera.cpp",
    ],
    hdrs = [
        "calibration.h",
        "camera.h",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        "@eigen",
        "@nholthaus//:units",
        "@opencv",
    ],
)
