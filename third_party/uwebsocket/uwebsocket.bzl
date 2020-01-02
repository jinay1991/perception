def uwebsocket():
    if "uwebsocket" not in native.existing_rules():
        native.new_local_repository(
            name = "uwebsocket",
            build_file = "//third_party/uwebsocket:uwebsocket.BUILD",
            path = "/usr/",
        )
