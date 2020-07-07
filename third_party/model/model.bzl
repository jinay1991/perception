load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def model():
    """ Load ML Models as Dependency """
    if "ssd_mobilenet_v2_coco" not in native.existing_rules():
        http_archive(
            name = "ssd_mobilenet_v2_coco",
            build_file = "//third_party/model:model.BUILD",
            strip_prefix = "ssd_mobilenet_v2_coco_2018_03_29",
            sha256 = "b9380178b2e35333f1a735e39745928488bdabeb9ed20bc6fa07af8172cb5adc",
            url = "http://download.tensorflow.org/models/object_detection/ssd_mobilenet_v2_coco_2018_03_29.tar.gz",
        )

    if "ssdlite_mobilenet_v2_coco" not in native.existing_rules():
        http_archive(
            name = "ssdlite_mobilenet_v2_coco",
            build_file = "//third_party/model:model.BUILD",
            strip_prefix = "ssdlite_mobilenet_v2_coco_2018_05_09",
            sha256 = "542445cce834dbfbb7df1991425d475e85a2d7ec68c60a4f262bb18aac10c8b2",
            url = "http://download.tensorflow.org/models/object_detection/ssdlite_mobilenet_v2_coco_2018_05_09.tar.gz",
        )

    if "ssd_mobilenet_v3_large_coco" not in native.existing_rules():
        http_archive(
            name = "ssd_mobilenet_v3_large_coco",
            build_file = "//third_party/model:model.BUILD",
            strip_prefix = "ssd_mobilenet_v3_large_coco_2020_01_14",
            sha256 = "8dade970d957ae5cb8b47e9fcefbe124e40b38c8641e484d2ab15b81d9b5126f",
            url = "http://download.tensorflow.org/models/object_detection/ssd_mobilenet_v3_large_coco_2020_01_14.tar.gz",
        )
