load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

CUDA_ARCHIVE_BASE_URL = "https://developer.download.nvidia.com/compute/cuda/redist/"

def cuda():
    """
    Load CUDA Toolkit as third party
    """
    maybe(
        http_archive,
        name = "cuda_cccl",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_cccl/linux-x86_64/cuda_cccl-linux-x86_64-11.7.58-archive.tar.xz",
        sha256 = "a66261d174a3f8fea87e0dc91e5cd084dda89be8bb0a1f5ca0ab5d05a93ade4a",
        strip_prefix = "cuda_cccl-linux-x86_64-11.7.58-archive",
        build_file = "//third_party/cuda:cuda_cccl.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cudart",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_cudart/linux-x86_64/cuda_cudart-linux-x86_64-11.7.60-archive.tar.xz",
        sha256 = "1c079add60a107f6dd9e72a0cc9cde03eb9d833506f355c22b9177c47a977552",
        strip_prefix = "cuda_cudart-linux-x86_64-11.7.60-archive",
        build_file = "//third_party/cuda:cuda_cudart.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cuobjdump",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_cuobjdump/linux-x86_64/cuda_cuobjdump-linux-x86_64-11.7.50-archive.tar.xz",
        sha256 = "f901085d83f83ae549de45e4410c74c3adddd2d541ba2780c23105df39008820",
        strip_prefix = "cuda_cuobjdump-linux-x86_64-11.7.50-archive",
        build_file = "//third_party/cuda:cuda_cuobjdump.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cupti",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_cupti/linux-x86_64/cuda_cupti-linux-x86_64-11.7.50-archive.tar.xz",
        sha256 = "441f7da2608d1965f0e3e2e03aeea86b0a3454cbea8e7af8112529c9acef3853",
        strip_prefix = "cuda_cupti-linux-x86_64-11.7.50-archive",
        build_file = "//third_party/cuda:cuda_cupti.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cuxxfilt",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_cuxxfilt/linux-x86_64/cuda_cuxxfilt-linux-x86_64-11.7.50-archive.tar.xz",
        sha256 = "8a9cb0af698fe39c1b92d179e9ac22e8acb752eb8c531dbfdd049ddcd3c2caa6",
        strip_prefix = "cuda_cuxxfilt-linux-x86_64-11.7.50-archive",
        build_file = "//third_party/cuda:cuda_cuxxfilt.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_nvcc",
        url = CUDA_ARCHIVE_BASE_URL + "cuda_nvcc/linux-x86_64/cuda_nvcc-linux-x86_64-11.7.64-archive.tar.xz",
        sha256 = "7721fcfa3eb183ecb1d7fe138ce52d8238f0a6ecf1e9964cf8cfe5d8b7ec3c92",
        strip_prefix = "cuda_nvcc-linux-x86_64-11.7.64-archive",
        build_file = "//third_party/cuda:cuda_nvcc.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cublas",
        url = CUDA_ARCHIVE_BASE_URL + "libcublas/linux-x86_64/libcublas-linux-x86_64-11.10.1.25-archive.tar.xz",
        sha256 = "27f5975b0b373f5fc96ac2f4ec9f28de3eb07f674acc0b0a5262dd2c76ddc5ff",
        strip_prefix = "libcublas-linux-x86_64-11.10.1.25-archive",
        build_file = "//third_party/cuda:cuda_cublas.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cufft",
        url = CUDA_ARCHIVE_BASE_URL + "libcufft/linux-x86_64/libcufft-linux-x86_64-10.7.2.50-archive.tar.xz",
        sha256 = "70c4c2abb9d77210a5d2313abfdddf1857d654d1cf925946a645793bc14714c5",
        strip_prefix = "libcufft-linux-x86_64-10.7.2.50-archive",
        build_file = "//third_party/cuda:cuda_cufft.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_curand",
        url = CUDA_ARCHIVE_BASE_URL + "libcurand/linux-x86_64/libcurand-linux-x86_64-10.2.10.50-archive.tar.xz",
        sha256 = "a05411f1775d5783800b71f6b43fae660e3baf900ae07efb853e615116ee479b",
        strip_prefix = "libcurand-linux-x86_64-10.2.10.50-archive",
        build_file = "//third_party/cuda:cuda_curand.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cusolver",
        url = CUDA_ARCHIVE_BASE_URL + "libcusolver/linux-x86_64/libcusolver-linux-x86_64-11.3.5.50-archive.tar.xz",
        sha256 = "7ed168c7fda04a4a640f6225cb76d5251a39e3d35db7630d3646cec58de724f8",
        strip_prefix = "libcusolver-linux-x86_64-11.3.5.50-archive",
        build_file = "//third_party/cuda:cuda_cusolver.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_cusparse",
        url = CUDA_ARCHIVE_BASE_URL + "libcusparse/linux-x86_64/libcusparse-linux-x86_64-11.7.3.50-archive.tar.xz",
        sha256 = "c56ddd2d4deebb02bf1e082905f13cac7c685bfa415f1c489dd5fe382cf1f5de",
        strip_prefix = "libcusparse-linux-x86_64-11.7.3.50-archive",
        build_file = "//third_party/cuda:cuda_cusparse.BUILD",
    )

    maybe(
        http_archive,
        name = "cuda_nvjpeg",
        url = CUDA_ARCHIVE_BASE_URL + "libnvjpeg/linux-x86_64/libnvjpeg-linux-x86_64-11.7.2.34-archive.tar.xz",
        sha256 = "0457a11af6903d63aec942e2884e02002c3d579071eacd89f08a25cab339f5eb",
        strip_prefix = "libnvjpeg-linux-x86_64-11.7.2.34-archive",
        build_file = "//third_party/cuda:cuda_nvjpeg.BUILD",
    )

    if "cuda" not in native.existing_rules():
        native.new_local_repository(
            name = "cuda",
            path = "/usr/local",
            build_file = "//third_party/cuda:cuda.BUILD",
        )
