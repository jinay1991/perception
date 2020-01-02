load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def rules_foreign_cc():
    if "rules_foreign_cc" not in native.existing_rules():
        http_archive(
            name = "rules_foreign_cc",
            strip_prefix = "rules_foreign_cc-master",
            sha256 = "a2e43b2141cddce94999e26de8075031394ac11fb8075de8aa0b8e13905715ed",
            url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
        )
