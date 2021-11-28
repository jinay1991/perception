cc_library(
    name = "common",
    hdrs = [
        "circular_bitset.h",
        "current_previous.h",
        "event_monitor.h",
        "filter.h",
        "finite_state_machine.h",
        "geometry.h",
        "linear_kalman_filter.h",
        "logging.h",
        "matrix.h",
        "toggle.h",
        "validity_range.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception:__subpackages__"],
    deps = [
        "@eigen",
        "@glog",
    ],
)
