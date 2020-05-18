load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lifecycle",
    srcs = ["node.cpp"],
    hdrs = [
        "i_node.h",
        "node.h",
    ],
    deps = [
        "//perception/middleware/communication",
    ],
)
