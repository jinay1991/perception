load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def opencv():
    if "opencv" not in native.existing_rules():
        http_archive(
            name = "opencv",
            build_file = "//third_party/opencv:opencv.BUILD",
            url = "https://github.com/jinay1991/perception/releases/download/v1.6/libopencv_dev-4.5.0-linux-no-gui.tar.gz",
            sha256 = "48ae02b3355071ac1fb9dd843ac37c605eb87fb4662ea7266451b456d60447a4",
        )
