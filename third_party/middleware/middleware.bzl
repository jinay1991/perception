load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def middleware():
    """ Load middleware """
    if "middleware" not in native.existing_rules():
        http_archive(
            name = "middleware",
            url = "https://gitlab.com/ad_platform/middleware/-/archive/v1.1/middleware-v1.1.tar.gz",
            strip_prefix = "middleware-v1.1",
            sha256 = "d84d4841cff8c7f7bee75f3c44ac5b4bf2cdce877f472f988d83e048837ffc2d",
        )
