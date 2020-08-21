load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def toolchain():
    if "com_grail_bazel_toolchain" not in native.existing_rules():
        http_archive(
            name = "com_grail_bazel_toolchain",
            strip_prefix = "bazel-toolchain-master",
            urls = ["https://github.com/grailbio/bazel-toolchain/archive/master.tar.gz"],
        )
