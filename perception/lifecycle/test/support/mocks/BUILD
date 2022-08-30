cc_library(
    name = "mocks",
    testonly = True,
    hdrs = [
        "node_mock.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception/lifecycle/test/support:__subpackages__"],
    deps = [
        "//perception/lifecycle",
    ],
)
