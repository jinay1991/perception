load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def opencv():
    if "opencv" not in native.existing_rules():
        http_archive(
            name = "opencv",
            build_file = "//third_party/opencv:opencv.BUILD",
            strip_prefix = "opencv-3.4.9",
            sha256 = "8a6da8f73cb8a6384e94698f057d7cc60a1c9cab87fd90f824c0f0108ebd59af",
            url = "https://github.com/opencv/opencv/archive/3.4.9.zip",
        )
