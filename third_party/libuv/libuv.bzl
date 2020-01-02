def libuv():
    if "libuv" not in native.existing_rules():
        native.new_local_repository(
            name = "libuv",
            build_file = "//third_party/libuv:libuv.BUILD",
            path = "/usr/",
        )
