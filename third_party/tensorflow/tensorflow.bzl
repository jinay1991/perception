load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tensorflow():
    """ Load TensorFlow as Dependency """
    if "tensorflow" not in native.existing_rules():
        http_archive(
            name = "tensorflow",
            sha256 = "973005dd379f64e901563da6318559670d22fe973c8dbc9a8e5ab245a6b656a1",
            url = "https://github.com/jinay1991/perception/releases/download/v1.0/libtensorflow_cc-2.3.0-linux.tar.gz",
        )
