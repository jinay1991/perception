cc_library(
    name = "datatypes",
    hdrs = [
        "driver_camera.h",
        "inference_engine_type.h",
        "lane.h",
        "traffic_light.h",
        "traffic_sign.h",
        "vehicle_dynamics.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@nholthaus//:units",
        "@opencv//:core",
    ],
)
