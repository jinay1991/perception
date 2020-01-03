load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_deb", "pkg_tar")

exports_files(glob([
    "data/*.bmp",
    "data/*.jpg",
    "data/*.txt",
]))

filegroup(
    name = "testdata",
    srcs = [
        "data/grace_hopper.bmp",
        "data/grace_hopper.jpg",
    ],
)

cc_library(
    name = "simulation",
    srcs = glob(
        ["src/**/*.cpp"],
        exclude = ["src/main.cpp"],
    ),
    hdrs = glob([
        "include/**/*.h",
    ]),
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
    includes = ["include"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lib:perception",
        "@eigen",
        "@nlohmann//:json",
        "@uwebsocket",
    ],
)

cc_binary(
    name = "client-app",
    srcs = ["src/main.cpp"],
    copts = [
        "-std=c++14",
        "-Wall",
        "-Werror",
    ],
    data = [
        ":testdata",
    ],
    includes = ["include"],
    linkstatic = True,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":simulation",
    ],
)

pkg_tar(
    name = "perception_bin_pkg",
    testonly = True,
    srcs = [
        ":client-app",
        "//lib:perception_tests",
    ],
    extension = "tar.gz",
    package_dir = "/opt/perception/bin",
    strip_prefix = "/",
    tags = ["manual"],
)

pkg_tar(
    name = "perception_lib_pkg",
    testonly = True,
    srcs = [
        "//lib:perception",
    ],
    extension = "tar.gz",
    package_dir = "/opt/perception",
    strip_prefix = "/",
    tags = ["manual"],
    visibility = ["//visibility:public"],
)

pkg_tar(
    name = "perception_hdrs_pkg",
    testonly = True,
    srcs = glob([
        "lib/include/**/*.h",
    ]),
    extension = "tar.gz",
    package_dir = "/opt/perception",
    strip_prefix = "/",
    tags = ["manual"],
    visibility = ["//visibility:public"],
)

pkg_tar(
    name = "perception_tar_pkg",
    testonly = True,
    extension = "tar.gz",
    tags = ["manual"],
    visibility = ["//visibility:public"],
    deps = [
        ":perception_bin_pkg",
        ":perception_hdrs_pkg",
        ":perception_lib_pkg",
    ],
)

pkg_deb(
    name = "perception_deb_pkg",
    testonly = True,
    architecture = "amd64",
    data = ":perception_tar_pkg",
    description = "Motion Planning for Automonous Vehicle Driving",
    homepage = "https://gitlab.com/jinay1991/perception",
    maintainer = "https://gitlab.com/jinay1991",
    package = "perception",
    tags = ["manual"],
    version = "0.0.2",
    visibility = ["//visibility:public"],
)
