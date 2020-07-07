package(default_visibility = ["//visibility:public"])

filegroup(
    name = "checkpoint",
    srcs = glob(["*.ckpt.*"]) + ["checkpoint"],
)

filegroup(
    name = "saved_model",
    srcs = glob(["saved_model/*"]),
)

filegroup(
    name = "frozen_graph",
    srcs = glob(["*.pb"]),
)

filegroup(
    name = "tflite",
    srcs = glob(["*.tflite"]),
)
