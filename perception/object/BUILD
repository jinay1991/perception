cc_library(
    name = "object",
    srcs = ["object.cpp"],
    hdrs = ["object.h"],
    data = [
        "@ssd_mobilenet_v2_coco//:saved_model",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//perception/inference_engine",
        "//perception/object/datatype",
        "//perception/sensor/camera/datatype",
        "@opencv",
    ],
)
