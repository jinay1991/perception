cc_library(
    name = "driver_camera",
    srcs = [
        "driver_camera.cpp",
    ],
    hdrs = [
        "driver_camera.h",
    ],
    data = [
        "@opencv//:haarcascades",
        "@opencv//:lbpcascades",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/common:logging",
        "//perception/datatypes",
        "//perception/driver/datatype",
        "//perception/sensor/camera/datatype",
        "@opencv",
    ],
)
