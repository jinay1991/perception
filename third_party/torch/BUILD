licenses(["notice"])

alias(
    name = "torch",
    actual = select(
        {
            "//bazel/platforms:macos": "@torch_macos//:torch",
            "//bazel/platforms:linux": "@torch_linux//:torch",
        },
        no_match_error = "No known platform specified.",
    ),
    visibility = ["//visibility:public"],
)
