load("@rules_cc//cc:defs.bzl", "cc_library")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "tflite_inference_engine",
    srcs = [
        "tflite_inference_engine.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "tflite_inference_engine.h",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        "@tensorflowlite",
    ],
)

cc_library(
    name = "tf_inference_engine",
    srcs = [
        "tf_inference_engine.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "tf_inference_engine.h",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        "@tensorflow",
    ],
)

cc_library(
    name = "torch_inference_engine",
    srcs = [
        "torch_inference_engine.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "torch_inference_engine.h",
    ],
    deps = [
        "//perception/common/logging",
        "//perception/datatypes",
        # "@torch",
    ],
)

cc_library(
    name = "inference_engine",
    srcs = [
        "inference_engine_strategy.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "inference_engine_strategy.h",
    ],
    deps = [
        ":tf_inference_engine",
        ":tflite_inference_engine",
        ":torch_inference_engine",
        "//perception/common/logging",
        "//perception/datatypes",
    ],
)

pkg_tar(
    name = "includes",
    srcs = glob(["*.h"]),
    mode = "0644",
    package_dir = "perception/inference_engine",
    tags = ["manual"],
)
