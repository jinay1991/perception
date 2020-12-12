load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "support",
    testonly = True,
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = ["//perception/driver:__subpackages__"],
    deps = [
        ":builders",
        ":mocks",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//middleware/communication",
        "@middleware//middleware/lifecycle",
        "@middleware//middleware/lifecycle/test:test_support",
    ],
)

cc_library(
    name = "builders",
    testonly = True,
    srcs = glob(["builders/*.cpp"]),
    hdrs = glob(["builders/*.h"]),
    deps = ["//perception/datatypes"],
)

cc_library(
    name = "mocks",
    testonly = True,
    srcs = glob(["mocks/*.cpp"]),
    hdrs = glob(["mocks/*.h"]),
    deps = ["//perception/driver"],
)
