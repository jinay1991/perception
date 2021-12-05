cc_test(
    name = "benchmark_tests",
    srcs = [
        "finite_state_machine_benchmark_tests.cpp",
    ],
    features = [
        "treat_warnings_as_errors",
        "strict_warnings",
    ],
    tags = ["benchmark"],
    deps = [
        "//perception/common",
        "@benchmark//:benchmark_main",
    ],
)
