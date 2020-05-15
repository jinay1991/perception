load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gomp",
    srcs = ["lib/libgomp-75eea7e8.so.1"],
    linkopts = [
        "-lpthread",
        "-ldl",
    ],
    alwayslink = True,
)

cc_library(
    name = "torch_cpu",
    srcs = ["lib/libtorch_cpu.so"],
    linkopts = [
        "-lpthread",
        "-ldl",
    ],
    deps = [
        ":gomp",
    ],
)

cc_library(
    name = "nnpack",
    srcs = ["lib/libnnpack.a"],
)

cc_library(
    name = "pytorch_qnnpack",
    srcs = ["lib/libpytorch_qnnpack.a"],
)

cc_library(
    name = "XNNPACK",
    srcs = ["lib/libXNNPACK.a"],
)

cc_library(
    name = "cpuinfo",
    srcs = [
        "lib/libcpuinfo.a",
        "lib/libcpuinfo_internals.a",
    ],
)

cc_library(
    name = "clog",
    srcs = ["lib/libclog.a"],
)

cc_library(
    name = "caffe2",
    srcs = glob([
        "lib/libcaffe2_*",
    ]),
    linkopts = [
        "-lpthread",
        "-lm",
        "-ldl",
    ],
    deps = [
        ":c10",
        ":gomp",
        ":torch",
        ":torch_cpu",
    ],
)

cc_library(
    name = "c10",
    srcs = ["lib/libc10.so"],
    linkopts = [
        "-lpthread",
        "-lm",
        "-ldl",
    ],
    deps = [
        ":gomp",
    ],
)

cc_library(
    name = "torch",
    srcs = ["lib/libtorch.so"],
    hdrs = glob([
        "include/**/*.h",
        "include/**/*",
    ]),
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
    linkopts = [
        "-lpthread",
        "-lm",
        "-ldl",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":XNNPACK",
        ":c10",
        ":clog",
        ":cpuinfo",
        ":gomp",
        ":nnpack",
        ":pytorch_qnnpack",
        ":torch_cpu",
    ],
)
