load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def opencv():
    if "opencv_macos" not in native.existing_rules():
        http_archive(
            name = "opencv_macos",
            build_file = "//third_party/opencv:opencv.BUILD",
            strip_prefix = "opencv/4.2.0",
            sha256 = "f53dd07aea7163aff1d30ec9cd6b4d2a49db5362e5845b690284b4f0574f09db",
            url = "https://homebrew.bintray.com/bottles/opencv-4.2.0.catalina.bottle.tar.gz",
        )
    if "opencv_linux" not in native.existing_rules():
        native.new_local_repository(
            name = "opencv_linux",
            build_file = "//third_party/opencv:opencv.BUILD",
            path = "/usr/local",
        )
