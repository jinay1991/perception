load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "topic",
    hdrs = [
        "basic_topics.h",
        "i_topic.h",
        "topic.h",
    ],
    deps = [
        "//perception/datatypes",
    ],
)

cc_library(
    name = "lifecycle",
    srcs = ["node.cpp"],
    hdrs = [
        "i_node.h",
        "node.h",
    ],
    deps = [
        ":topic",
        "//perception/middleware/communication",
    ],
)
