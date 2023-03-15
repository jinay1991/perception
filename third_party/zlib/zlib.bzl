load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def zlib():
    if "zlib" not in native.existing_rules():
        http_archive(
            name = "zlib",
            build_file = "//third_party/zlib:zlib.BUILD",
            sha256 = "b3a24de97a8fdbc835b9833169501030b8977031bcb54b3b3ac13740f846ab30",
            strip_prefix = "zlib-1.2.13",
            url = "https://zlib.net/zlib-1.2.13.tar.gz",
        )
