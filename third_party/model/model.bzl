load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def model():
    """ Load ML Models as Dependency """
    if "ssd_mobilenet_v2_coco" not in native.existing_rules():
        http_archive(
            name = "ssd_mobilenet_v2_coco",
            build_file = "//third_party/model:model.BUILD",
            strip_prefix = "ssd_mobilenet_v2_coco_2018_03_29",
            sha256 = "86babf46e9f21f8e1fb0af1945981a422226f51d42dd3c6ab104a72295994ba7",
            url = "https://github.com/jinay1991/perception/releases/download/v0.5/ssd_mobilenet_v2_coco_2018_03_29.tar.gz",
        )
