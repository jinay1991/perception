load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def compile_commands():
    if "compile_commands" not in native.existing_rules():
        http_archive(
            name = "compile_commands",
            strip_prefix = "bazel-compilation-database-master",
            urls = ["https://github.com/grailbio/bazel-compilation-database/archive/master.tar.gz"],
        )
