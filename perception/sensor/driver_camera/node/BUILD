cc_library(
    name = "node",
    srcs = ["driver_camera_node.cpp"],
    hdrs = ["driver_camera_node.h"],
    data = [
        "//:testdata",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/communication:topics",
        "//perception/sensor/driver_camera",
        "@middleware//:communication",
        "@middleware//:lifecycle",
    ],
)
