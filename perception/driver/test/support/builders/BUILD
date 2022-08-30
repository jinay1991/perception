cc_library(
    name = "builders",
    testonly = True,
    srcs = [
        "driver_camera_message_builder.cpp",
    ],
    hdrs = [
        "driver_camera_message_builder.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = [
        "//perception/driver/test:__subpackages__",
    ],
    deps = [
        "//perception/driver/datatype",
    ],
)
