config_setting(
    name = "debug_build",
    values = {
        "compilation_mode": "dbg",
    },
)

config_setting(
    name = "darwin",
    constraint_values = ["@bazel_tools//platforms:osx"],
)

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
    defines = select({
        ":debug_build": ["NDEBUG"],
        "//conditions:default": [],
    }),
    includes = ["include"],
    tags = ["lib"],
    visibility = [
        "//visibility:public",
    ],
    deps = ["@nholthaus//:units"] + select({
        "darwin": ["@torch-macos//:libtorch"],
        "//conditions:default": ["@torch-linux//:libtorch"],
    }),
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
