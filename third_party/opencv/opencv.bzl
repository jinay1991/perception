load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def opencv():
    if "opencv" not in native.existing_rules():
        http_archive(
            name = "opencv",
            url = "https://github.com/jinay1991/artifactory/releases/download/v1.0/libopencv_dev-4.5.0-linux.tar.gz",
            sha256 = "01f39b03af48dec4f4c58a86f4fa850112cb3dd6c506fd12ce2302d2a9f4d6bb",
        )
