load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def opencv():
    if "opencv" not in native.existing_rules():
        http_archive(
            name = "opencv",
            url = "https://github.com/jinay1991/perception/releases/download/v1.0/libopencv_dev-4.5.0-linux.tar.gz",
            sha256 = "97b67c8a8c1131f51c16282f4e97e71717af6496c0c22d8563aa83837e43dcae",
        )
