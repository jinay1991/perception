load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def eigen():
    if "eigen" not in native.existing_rules():
        http_archive(
            name = "eigen",
            build_file = "//third_party/eigen:eigen.BUILD",
            strip_prefix = "eigen-3.3.7",
            sha256 = "e09b89aae054e9778ee3f606192ee76d645eec82c402c01c648b1fe46b6b9857",
            url = "https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.zip",
        )
