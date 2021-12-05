package(default_visibility = ["//visibility:public"])

cc_library(
    name = "torch",
    srcs = [
        "lib/libc10.so",
        "lib/libcaffe2_detectron_ops.so",
        "lib/libcaffe2_module_test_dynamic.so",
        "lib/libcaffe2_observers.so",
        "lib/libgomp-75eea7e8.so.1",
        "lib/libtensorpipe.so",
        "lib/libtorch.so",
        "lib/libtorch_cpu.so",
        "lib/libtorch_global_deps.so",
    ],
    hdrs = glob([
        "include/torch/**/*.h",
        "include/caffe2/**/*.h",
        "include/torch/csrc/api/include/**/*.h",
        "include/c10/**/*.h",
        "include/ATen/**/*.h",
    ]),
    copts = ["-std=c++14"],
    includes = [
        "include",
        "include/torch/csrc/api/include",
    ],
)
