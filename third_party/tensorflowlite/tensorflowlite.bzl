load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflowlite():
    """ Load TensorFlow Lite as Dependency """
    if "tensorflowlite" not in native.existing_rules():
        http_archive(
            name = "tensorflowlite",
            sha256 = "7576e61634dd51620b821460b36f1add2aa7444c81cdd6104c1b19b816df6b75",
            strip_prefix = "libtensorflowlite_cc-2.3.0-linux",
            url = "https://github.com/jinay1991/perception/releases/download/v0.5/libtensorflowlite_cc-2.3.0-linux.tar.gz",
        )
