load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflow():
    """ Load TensorFlow as Dependency """
    if "bazel_skylib" not in native.existing_rules():
        http_archive(
            name = "bazel_skylib",
            urls = [
                "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
                "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
            ],
            sha256 = "97e70364e9249702246c0e9444bccdc4b847bed1eb03c5a3ece4f83dfe6abc44",
        )

    if "com_google_absl" not in native.existing_rules():
        http_archive(
            name = "com_google_absl",
            sha256 = "f368a8476f4e2e0eccf8a7318b98dafbe30b2600f4e3cf52636e5eb145aba06a",
            strip_prefix = "abseil-cpp-df3ea785d8c30a9503321a3d35ee7d35808f190d",
            url = "https://github.com/abseil/abseil-cpp/archive/df3ea785d8c30a9503321a3d35ee7d35808f190d.tar.gz",
        )

    if "com_google_protobuf" not in native.existing_rules():
        http_archive(
            name = "com_google_protobuf",
            url = "https://github.com/protocolbuffers/protobuf/archive/v3.9.2.zip",
            sha256 = "cfcba2df10feec52a84208693937c17a4b5df7775e1635c1e3baffc487b24c9b",
            strip_prefix = "protobuf-3.9.2",
        )

    if "tensorflow" not in native.existing_rules():
        http_archive(
            name = "tensorflow",
            build_file = "//third_party/tensorflow:tensorflow.BUILD",
            sha256 = "9aa8f085804933d759dd2ca4b438b0e0beff0f4acf119781d143151543b7b9c0",
            strip_prefix = "libtensorflow_cc-2.3.0-linux",
            url = "https://github.com/jinay1991/perception/releases/download/v0.1/libtensorflow_cc-2.3.0-linux.tar.gz",
        )
