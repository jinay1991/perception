cc_library(
    name = "kalman_filter",
    hdrs = [
        "linear_kalman_filter.h",
        "multivariate_moments.h",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    visibility = ["//perception:__subpackages__"],
    deps = [
        "@eigen",
    ],
)
