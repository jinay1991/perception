load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "topics",
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@middleware//middleware/communication",
    ],
)
