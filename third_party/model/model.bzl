load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def model():
    """ Load ML Models as Dependency """
    if "ssd_mobilenet_v2_coco" not in native.existing_rules():
        http_archive(
            name = "ssd_mobilenet_v2_coco",
            sha256 = "a53855bdebbcc520c296a0c140bc3bfb0aebebd4a979e970e0242780bb60417d",
            url = "https://github.com/jinay1991/artifactory/releases/download/v1.0/ssd_mobilenet_v2_coco_2018_03_29.tar.gz",
        )
