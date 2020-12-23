load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "driver",
    srcs = [
        "data_source.cpp",
        "driver.cpp",
        "fatigue.cpp",
        "fatigue_message_builder.cpp",
        "parameter_handler.cpp",
        "perclos.cpp",
        "visual_attention.cpp",
    ],
    hdrs = [
        "data_source.h",
        "driver.h",
        "fatigue.h",
        "fatigue_message_builder.h",
        "i_data_source.h",
        "i_parameter_handler.h",
        "parameter_handler.h",
        "parameters.h",
        "perclos.h",
        "visual_attention.h",
    ],
    copts = [
        "-Wall",
        "-Werror",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
    ],
)
