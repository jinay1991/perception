load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def libuv():
    if "libuv" not in native.existing_rules():
        http_archive(
            name = "libuv",
            build_file = "//third_party/libuv:libuv.BUILD",
            strip_prefix = "libuv-1.34.0",
            sha256 = "9a4bb2b40cd4c6afd25d4c6cf5df0136794850dc7684ba08fc7da775710d3d0c",
            url = "https://github.com/libuv/libuv/archive/v1.34.0.zip",
        )
