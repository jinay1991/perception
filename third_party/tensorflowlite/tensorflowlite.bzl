load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflowlite():
    """ Load TensorFlow Lite as Dependency """
    if "tensorflowlite" not in native.existing_rules():
        http_archive(
            name = "tensorflowlite",
            sha256 = "d8cdfc3e96ca8c2057acd4c5caaa19e335305334adc50bc0ec8872108e0f81e9",
            url = "https://github.com/jinay1991/perception/releases/download/v1.0/libtensorflowlite_cc-2.3.0-linux.tar.gz",
        )
