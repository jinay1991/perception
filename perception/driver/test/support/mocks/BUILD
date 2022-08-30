cc_library(
    name = "mocks",
    testonly = True,
    srcs = [],
    hdrs = [
        "data_source_mock.h",
        "parameter_handler_mock.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/driver/test:__subpackages__"],
    deps = [
        "//perception/driver",
    ],
)
