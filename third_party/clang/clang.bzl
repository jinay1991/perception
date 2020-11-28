load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def clang():
    if "clang" not in native.existing_rules():
        http_archive(
            name = "clang",
            build_file = "//third_party/clang:clang.BUILD",
            sha256 = "a23b082b30c128c9831dbdd96edad26b43f56624d0ad0ea9edec506f5385038d",
            strip_prefix = "clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/bin",
            url = "http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz",
        )

    if "bazel_compilation_database" not in native.existing_rules():
        http_archive(
            name = "bazel_compilation_database",
            url = "https://github.com/grailbio/bazel-compilation-database/archive/0.4.5.tar.gz",
            strip_prefix = "bazel-compilation-database-0.4.5",
            sha256 = "bcecfd622c4ef272fd4ba42726a52e140b961c4eac23025f18b346c968a8cfb4",
        )
