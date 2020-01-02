load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def torch():
    if "torch" not in native.existing_rules():
        http_archive(
            name = "torch",
            build_file = "//third_party/torch:torch.BUILD",
            sha256 = "eda550df98414e4f90a854c2220da354fe50692a8e55a53e999d36dbae4cd506",
            strip_prefix = "libtorch",
            url = "https://download.pytorch.org/libtorch/cpu/libtorch-macos-1.3.1.zip",
        )
