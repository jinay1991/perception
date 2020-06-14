load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def middleware():
    """ Load middleware """
    if "middleware" not in native.existing_rules():
        git_repository(
            name = "middleware",
            remote = "https://gitlab.com/ad_platform/middleware.git",
            branch = "master",
        )
