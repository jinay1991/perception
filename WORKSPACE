workspace(name = "perception")

load("@perception//third_party:dependencies.bzl", "third_party_deps")

third_party_deps()

## Load TensorFlow as Submodule
load("@org_tensorflow//tensorflow:workspace.bzl", "tf_workspace")

tf_workspace(tf_repo_name = "org_tensorflow")
