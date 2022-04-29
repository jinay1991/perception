load("@perception//third_party/benchmark:benchmark.bzl", "benchmark")
load("@perception//third_party/eigen:eigen.bzl", "eigen")
load("@perception//third_party/glog:glog.bzl", "glog")
load("@perception//third_party/googletest:googletest.bzl", "googletest")
load("@perception//third_party/libuv:libuv.bzl", "libuv")
load("@perception//third_party/llvm_toolchain:llvm_toolchain.bzl", "llvm_toolchain")
load("@perception//third_party/model:model.bzl", "model")
load("@perception//third_party/nholthaus:nholthaus.bzl", "nholthaus")
load("@perception//third_party/nlohmann:nlohmann.bzl", "nlohmann")
load("@perception//third_party/opencv:opencv.bzl", "opencv")
load("@perception//third_party/openssl:openssl.bzl", "openssl")
load("@perception//third_party/sysroot:sysroot.bzl", "sysroot")
load("@perception//third_party/tensorflow:tensorflow.bzl", "tensorflow")
load("@perception//third_party/tensorflowlite:tensorflowlite.bzl", "tensorflowlite")
load("@perception//third_party/torch:torch.bzl", "torch")
load("@perception//third_party/uwebsocket:uwebsocket.bzl", "uwebsocket")
load("@perception//third_party/zlib:zlib.bzl", "zlib")

def perception_dependencies():
    """ Load 3rd party dependencies """
    benchmark()
    eigen()
    glog()
    googletest()
    libuv()
    llvm_toolchain()
    model()
    nholthaus()
    nlohmann()
    opencv()
    openssl()
    sysroot()
    tensorflow()
    tensorflowlite()
    torch()
    uwebsocket()
    zlib()
