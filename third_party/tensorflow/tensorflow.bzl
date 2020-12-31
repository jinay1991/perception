load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflow():
    """ Load TensorFlow as Dependency """
    if "tensorflow" not in native.existing_rules():
        http_archive(
            name = "tensorflow",
            sha256 = "5b7927556650c74dffc7cab9b431089436463479de5d5ecfc07f2ef67af33f9e",
            strip_prefix = "libtensorflow_cc-2.3.0-linux",
            url = "https://github.com/jinay1991/perception/releases/download/v0.5/libtensorflow_cc-2.3.0-linux.tar.gz",
        )
