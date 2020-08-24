load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "tensorflowlite",
    srcs = glob(
        ["lib/libtensorflowlite.*"],
        exclude = [
            "lib/*.params",
            "lib/*.runfiles_manifest",
        ],
    ),
    hdrs = glob([
        "include/**/*.h",
        "include/**/*",
    ]),
    includes = [
        "include",
    ],
    deps = [
        "@flatbuffers//:runtime_cc",
    ],
)
