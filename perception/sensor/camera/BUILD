cc_library(
    name = "camera",
    srcs = [
        "camera.cpp",
    ],
    hdrs = [
        "camera.h",
    ],
    data = [
        "//:calibration_data",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "//perception/sensor/calibration/camera",
        "@opencv",
    ],
)
