load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def torch():
    if "torch_macos" not in native.existing_rules():
        http_archive(
            name = "torch_macos",
            build_file = "//third_party/torch:torch.BUILD",
            sha256 = "eda550df98414e4f90a854c2220da354fe50692a8e55a53e999d36dbae4cd506",
            strip_prefix = "libtorch",
            url = "https://download.pytorch.org/libtorch/cpu/libtorch-macos-1.3.1.zip",
        )

    if "torch_linux" not in native.existing_rules():
        http_archive(
            name = "torch_linux",
            build_file = "//third_party/torch:torch.BUILD",
            sha256 = "3f36d7a20e2d8e65b4ba5f6b5a8ccab0bbf65f1e1ccc9c95eb6853b2278fdf45",
            strip_prefix = "libtorch",
            url = "https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.3.1%2Bcpu.zip",
        )
