cc_library(
    name = "lifecycle",
    srcs = [
        "node.cpp",
        "node.h",
        "node_runner.cpp",
        "node_runner.h",
        "null_node.h",
    ],
    hdrs = [
        "i_node.h",
        "i_node_runner.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = [
        "//application/driver:__subpackages__",
        "//perception/driver/node:__subpackages__",
        "//perception/lifecycle/test:__subpackages__",
    ],
)
