load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

MODULES = [
    "calib3d",
    "core",
    "dnn",
    "features2d",
    "flann",
    "highgui",
    "imgcodecs",
    "imgproc",
    "ml",
    "objdetect",
    "video",
    "videoio",
]

MODULE_DEPS = {
    "calib3d": [
        "core",
        "imgproc",
        "features2d",
        "flann",
    ],
    "features2d": [
        "core",
        "imgproc",
        "flann",
    ],
    "flann": ["core"],
    "highgui": [
        "core",
        "imgproc",
    ],
    "imgcodecs": [
        "core",
        "imgproc",
    ],
    "imgproc": ["core"],
    "ml": ["core"],
    "objdetect": [
        "core",
        "imgproc",
        "features2d",
        "flann",
        "calib3d",
    ],
    "dnn": [
        "core",
        "imgproc",
    ],
    "video": [
        "core",
        "imgproc",
        "features2d",
        "flann",
        "calib3d",
    ],
    "videoio": [
        "core",
        "imgproc",
        "imgcodecs",
    ],
}

[
    (
        cc_library(
            name = module,
            srcs = select({
                "@//bazel/platforms:macos": glob(["lib/libopencv_{}.dylib".format(module)]),
                "@//bazel/platforms:linux": glob(["lib/libopencv_{}.so*".format(module)]),
            }),
            hdrs = ["include/opencv4/opencv2/{}.hpp".format(module)] + glob(["include/opencv4/opencv2/{}/**/*.h*".format(module)]) +
                   ([
                       "include/opencv4/opencv2/cvconfig.h",
                       "include/opencv4/opencv2/opencv.hpp",
                       "include/opencv4/opencv2/opencv_modules.hpp",
                   ] if module == "core" else []),
            includes = ["include/opencv4"],
            deps = MODULE_DEPS[module] if module in MODULE_DEPS else [],
        )
    )
    for module in MODULES
]

# aggregate target
cc_library(
    name = "opencv",
    deps = MODULES,
)
