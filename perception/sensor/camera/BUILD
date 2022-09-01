cc_library(
    name = "camera",
    srcs = [
        "calibration.cpp",
        "calibration.h",
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
        "//perception/common:logging",
        "//perception/sensor/camera/datatype",
        "@opencv",
    ],
)
