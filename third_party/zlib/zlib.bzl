def zlib():
    if "zlib" not in native.existing_rules():
        native.new_local_repository(
            name = "zlib",
            build_file = "//third_party/zlib:zlib.BUILD",
            path = "/usr/",
        )
