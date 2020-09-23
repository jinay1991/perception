load("@//third_party/clang:clang.bzl", "clang")
load("@//third_party/compile_commands:compile_commands.bzl", "compile_commands")
load("@//third_party/eigen:eigen.bzl", "eigen")
load("@//third_party/googletest:googletest.bzl", "googletest")
load("@//third_party/libuv:libuv.bzl", "libuv")
load("@//third_party/middleware:middleware.bzl", "middleware")
load("@//third_party/model:model.bzl", "model")
load("@//third_party/nholthaus:nholthaus.bzl", "nholthaus")
load("@//third_party/nlohmann:nlohmann.bzl", "nlohmann")
load("@//third_party/opencv:opencv.bzl", "opencv")
load("@//third_party/openssl:openssl.bzl", "openssl")
load("@//third_party/tensorflow:tensorflow.bzl", "tensorflow")
load("@//third_party/tensorflowlite:tensorflowlite.bzl", "tensorflowlite")
load("@//third_party/torch:torch.bzl", "torch")
load("@//third_party/uwebsocket:uwebsocket.bzl", "uwebsocket")
load("@//third_party/zlib:zlib.bzl", "zlib")

def third_party_dependencies():
    """ Load 3rd party dependencies """
    clang()
    compile_commands()
    eigen()
    googletest()
    libuv()
    middleware()
    model()
    nholthaus()
    nlohmann()
    opencv()
    openssl()
    tensorflow()
    tensorflowlite()
    torch()
    uwebsocket()
    zlib()
