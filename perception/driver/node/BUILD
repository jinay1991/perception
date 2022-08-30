cc_library(
    name = "node",
    srcs = [
        "driver_node.cpp",
    ],
    hdrs = [
        "driver_node.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = [
        "//application/driver:__subpackages__",
        "//perception/driver/node/test:__subpackages__",
        "//sdk:__subpackages__",
    ],
    deps = [
        "//perception/driver",
        "//perception/lifecycle",
        "@nholthaus//:units",
    ],
)
