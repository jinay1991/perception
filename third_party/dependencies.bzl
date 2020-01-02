load("@//third_party/eigen:eigen.bzl", "eigen")
load("@//third_party/googletest:googletest.bzl", "googletest")
load("@//third_party/nholthaus:nholthaus.bzl", "nholthaus")
load("@//third_party/nlohmann:nlohmann.bzl", "nlohmann")
load("@//third_party/opencv:opencv.bzl", "opencv")
load("@//third_party/torch:torch.bzl", "torch")
load("@//third_party/uwebsocket:uwebsocket.bzl", "uwebsocket")

def third_party_deps():
    """ Load 3rd party dependencies """
    eigen()
    googletest()
    nholthaus()
    nlohmann()
    opencv()
    torch()
    uwebsocket()
