package(default_visibility = ["//visibility:public"])

CUDA_LIBS = [
    "cublas",
    "cublasLt",
    "cudart",
    "cudadevrt",
    "cudart_static",
    "cufft",
    "cufftw",
    "cuinj64",
    "cupti",
    "curand",
    "cusolver",
    "cusparse",
    "nppc",
    "nppial",
    "nppicc",
    "nppicom",
    "nppidei",
    "nppif",
    "nppig",
    "nppim",
    "nppi",
    "nppist",
    "nppisu",
    "nppitc",
    "npps",
    "nvblas",
    "nvgraph",
    "nvjpeg",
    "nvrtc-builtins",
    "nvrtc",
    "nvToolsExt",
    "OpenCL",
]

filegroup(
    name = "all_files",
    srcs = glob(["**"]),
)

filegroup(
    name = "nvcc",
    srcs = ["cuda/bin/nvcc"],
)

filegroup(
    name = "cicc",
    srcs = ["cuda/nvvm/bin/cicc"],
)

filegroup(
    name = "headers",
    srcs = glob([
        "cuda/**/*.h",
        "cuda/**/*.hpp",
        "cuda/include/**/*",
    ]),
)

filegroup(
    name = "libraries",
    srcs = glob([
        "cuda/lib64/**/*.so*",
    ]),
)

filegroup(
    name = "compiler_deps",
    srcs = [":headers"] +
           glob(
               [
                   "cuda/bin/**/*",
                   "cuda/nvvm/**/*",
               ],
               exclude = [
                   "cuda/nvvm/libnvvm-samples/*",
               ],
           ),
)

filegroup(
    name = "linker_deps",
    srcs = [":libraries"] +
           glob(
               [
                   "cuda/bin/**/*",
                   "cuda/nvvm/**/*",
               ],
               exclude = [
                   "cuda/nvvm/libnvvm-samples/*",
               ],
           ),
)

[
    cc_library(
        name = lib,
        srcs = glob([
            "cuda/lib64/lib{lib}.so*".format(lib = lib),
            "cuda/lib64/lib{lib}.a*".format(lib = lib),
        ]),
        hdrs = glob(["cuda/include/**/*"]),
        features = [
            "treat_warnings_as_errors",
            "strict_warnings",
        ],
        includes = ["cuda/include"],
        linkopts = [
            "-lrt",
            "-ldl",
            "-lpthread",
        ],
        linkstatic = 1,
    )
    for lib in CUDA_LIBS
]

cc_library(
    name = "cuda",
    deps = [":{lib}".format(lib = lib) for lib in CUDA_LIBS],
)
