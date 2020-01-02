load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def uwebsocket():
    if "uwebsocket" not in native.existing_rules():
        http_archive(
            name = "uwebsocket",
            build_file = "//third_party/uwebsocket:uwebsocket.BUILD",
            url = "https://github.com/uNetworking/uWebSockets/archive/v0.16.5.zip",
            sha256 = "326163696487b850b6ab2e273c026417737e1a8c751ea72fdec5c42c7d5377a1",
            strip_prefix = "uWebSockets-0.16.5",
        )
