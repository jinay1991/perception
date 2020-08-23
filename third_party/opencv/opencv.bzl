def opencv():
    if "opencv" not in native.existing_rules():
        native.new_local_repository(
            name = "opencv",
            build_file = "//third_party/opencv:opencv.BUILD",
            path = "/usr/local",
        )
