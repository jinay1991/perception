cc_library(
    name = "perception",
    srcs = glob([
        "src/**/*.cpp",
        "include/**/*.h",
    ]),
    hdrs = glob([
        "include/**/*.h",
    ]),
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
    includes = ["include"],
    tags = ["lib"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//third_party/opencv",
        "//third_party/torch",
        "@nholthaus//:units",
    ],
)

cc_test(
    name = "perception_unit_tests",
    srcs = glob(
        [
            "test/**/*.cpp",
        ],
        exclude = ["test/src/perception_test.cpp"],
    ),
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
    includes = ["test/include"],
    tags = [
        "test",
        "unit",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":perception",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "perception_component_tests",
    srcs = [
        "test/src/perception_test.cpp",
    ],
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
    includes = ["test/include"],
    tags = [
        "component",
        "test",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":perception",
        "@googletest//:gtest_main",
    ],
)
