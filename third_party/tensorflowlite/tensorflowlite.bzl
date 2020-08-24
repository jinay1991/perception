load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflowlite():
    """ Load TensorFlow Lite as Dependency """
    if "flatbuffers" not in native.existing_rules():
        http_archive(
            name = "flatbuffers",
            sha256 = "62f2223fb9181d1d6338451375628975775f7522185266cd5296571ac152bc45",
            strip_prefix = "flatbuffers-1.12.0",
            urls = [
                "https://storage.googleapis.com/mirror.tensorflow.org/github.com/google/flatbuffers/archive/v1.12.0.tar.gz",
                "https://github.com/google/flatbuffers/archive/v1.12.0.tar.gz",
            ],
        )
    if "tensorflowlite" not in native.existing_rules():
        http_archive(
            name = "tensorflowlite",
            build_file = "//third_party/tensorflowlite:tensorflowlite.BUILD",
            sha256 = "06b97d0cd672af17434e8a3fd67f0c97bd8f2715925eee4be515bc4f26b6acad",
            strip_prefix = "libtensorflowlite_cc-2.3.0-linux",
            url = "https://github.com/jinay1991/perception/releases/download/v0.1/libtensorflowlite_cc-2.3.0-linux.tar.gz",
        )
