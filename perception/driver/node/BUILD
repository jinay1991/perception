cc_library(
    name = "node",
    srcs = ["driver_node.cpp"],
    hdrs = ["driver_node.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/driver",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
