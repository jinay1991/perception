load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def middleware():
    """ Load middleware """
    if "middleware" not in native.existing_rules():
        http_archive(
            name = "middleware",
            sha256 = "6d506b2f86e1b65685a58430b843e39e40e39f3ea9ac21aa8f8660d8a4f1941b",
            url = ["https://gitlab.com/ad_platform/middleware/-/archive/v0.1/middleware-v0.1.zip"],
            strip_prefix = "middleware-v0.1",
        )
