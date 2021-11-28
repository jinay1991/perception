cc_library(
    name = "node",
    srcs = ["lane_node.cpp"],
    hdrs = ["lane_node.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/datatypes",
        "//perception/lane",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
