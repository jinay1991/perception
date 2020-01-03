licenses(["notice"])

alias(
    name = "opencv",
    actual = select(
        {
            "//bazel/platforms:macos": "@opencv_macos//:opencv",
            "//bazel/platforms:linux": "@opencv_linux//:opencv",
        },
        no_match_error = "No known platform specified.",
    ),
    visibility = ["//visibility:public"],
)
