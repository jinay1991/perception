exports_files(glob([
    "data/**/*.*",
]))

filegroup(
    name = "calibration_data",
    srcs = glob([
        "data/camera_calibration/**/*",
    ]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "testdata",
    srcs = glob([
        "data/*.jpg",
        "data/*.avi",
    ]),
    visibility = ["//visibility:public"],
)
