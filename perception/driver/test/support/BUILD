cc_library(
    name = "support",
    testonly = True,
    srcs = [
        "driver_simulator.cpp",
    ],
    hdrs = [
        "driver_simulator.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/driver/test:__subpackages__"],
    deps = [
        "//perception/driver/datatype",
        "//perception/driver/test/support/builders",
        "//perception/driver/test/support/mocks",
    ],
)
