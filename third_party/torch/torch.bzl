load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def torch():
    """ Load PyTorch (C++) Library dependencies """
    if "torch" not in native.existing_rules():
        http_archive(
            name = "torch",
            build_file = "//third_party/torch:torch.BUILD",
            sha256 = "c6c0d3a87039338f7812a1ae343b9e48198536f20d1415b0e5a9a15ba7b90b3f",
            url = "https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.6.0%2Bcpu.zip",
            strip_prefix = "libtorch",
        )
