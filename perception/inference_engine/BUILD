cc_library(
    name = "inference_engine",
    srcs = [
        "inference_engine_strategy.cpp",
        "null_inference_engine.cpp",
        "opencv_inference_engine.cpp",
        "tf_inference_engine.cpp",
        "tflite_inference_engine.cpp",
        "torch_inference_engine.cpp",
    ],
    hdrs = [
        "i_inference_engine.h",
        "inference_engine_strategy.h",
        "null_inference_engine.h",
        "opencv_inference_engine.h",
        "tf_inference_engine.h",
        "tflite_inference_engine.h",
        "torch_inference_engine.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/common",
        "//perception/datatypes",
        "@opencv//:dnn",
        "@tensorflow",
        "@tensorflowlite",
        "@torch",
    ],
)
