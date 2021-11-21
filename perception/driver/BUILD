load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver",
    srcs = [
        "data_source.cpp",
        "data_source.h",
        "driver.cpp",
        "eye_state_filter.cpp",
        "eye_state_filter.h",
        "fatigue.cpp",
        "fatigue_message_builder.cpp",
        "fatigue_message_builder.h",
        "parameter_handler.cpp",
        "parameter_handler.h",
        "parameters.h",
        "perclos.cpp",
        "perclos.h",
        "visual_attention.cpp",
    ],
    hdrs = [
        "driver.h",
        "fatigue.h",
        "i_data_source.h",
        "i_parameter_handler.h",
        "visual_attention.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
    ],
)
