load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//perception/datatypes",
    ],
)

cc_library(
    name = "node",
    srcs = glob(["node/*.cpp"]),
    hdrs = glob(["node/*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        ":driver",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
    ],
)
