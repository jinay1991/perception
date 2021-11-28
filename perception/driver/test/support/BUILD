cc_library(
    name = "support",
    testonly = True,
    srcs = [
        "driver_consumer_node.cpp",
        "driver_simulator_node.cpp",
    ],
    hdrs = [
        "driver_consumer_node.h",
        "driver_simulator_node.h",
        "operators.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/driver/test:__subpackages__"],
    deps = [
        ":builders",
        ":mocks",
        "//perception/communication:topics",
        "//perception/datatypes",
        "@middleware//:communication",
        "@middleware//:lifecycle",
        "@middleware//:support",
    ],
)

cc_library(
    name = "builders",
    testonly = True,
    srcs = ["builders/driver_camera_message_builder.cpp"],
    hdrs = ["builders/driver_camera_message_builder.h"],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/driver/test:__subpackages__"],
    deps = ["//perception/datatypes"],
)

cc_library(
    name = "mocks",
    testonly = True,
    hdrs = [
        "mocks/data_source_mock.h",
        "mocks/parameter_handler_mock.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/driver/test:__subpackages__"],
    deps = ["//perception/driver"],
)
