# Preception

[![pipeline status](https://gitlab.com/jinay1991/perception/badges/master/pipeline.svg)](https://gitlab.com/jinay1991/perception/commits/master)
[![coverage report](https://gitlab.com/jinay1991/perception/badges/master/coverage.svg?job=code-coverage)](https://jinay1991.gitlab.io/perception/)
[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://jinay1991.gitlab.io/perception/doc/html/)

[[Issue Board](https://gitlab.com/jinay1991/perception/-/boards)]

**WIP** Autonomous Driving Perception (with conjunction with Udacity Simulator) 

## Simulator

* Download prebuilt binaries
    * [Linux](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_linux.zip) 
    * [MacOS](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_mac.zip)
    * [MacOS Catalina v10.15](https://github.com/jinay1991/motion_planning/releases/download/v1.1/term3_sim_mac_catalina.zip)
    * [Windows](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_windows.zip)


## Build

* Build project
    * Release `bazel build //...`
    * Debug `bazel build -c dbg //...`
* Run Unit Tests `bazel test //... --test_output=all`

## Test

* Launch `Simulator`
* Run `./bazel-bin/client-app data/test_video.mp4`

## Dependencies

Install all the required dependencies:

```
sudo apt-get install -y build-essential gcc g++ lcov make cmake
sudo apt-get install -y openjdk-11-jdk openjdk-11-jre
sudo apt-get install -y libtool clang-format-6.0
sudo apt-get install -y git curl
sudo apt-get install -y wget
sudo apt-get install -y libuv1-dev libssl-dev
```

### OpenCV

Install OpenCV v4.x

On `macOS`, run `brew install opencv`.

On `Ubuntu` or other linux systems, run following commands to build OpenCV from source and install.

```
export OPENCV_VERSION="4.2.0"
wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip && \
unzip ${OPENCV_VERSION}.zip && rm -rf ${OPENCV_VERSION}.zip && \
mkdir -p opencv-${OPENCV_VERSION}/build
cd opencv-${OPENCV_VERSION}/build && \
cmake -DBUILD_TESTS=OFF -DBUILT_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DWITH_LIBV4L=ON -DWITH_OPENGL=ON .. && \
make -j8 && \
make install && \
cd -
rm -rf opencv-${OPENCV_VERSION}
```

## Supported OS 

Currently project works (tested) on following Operating Systems:

* macOS Catalina > v10.15
* Ubuntu 18.04
* Docker Engine v2.1.0 (stable)

## Third Party

Repository uses some of the third party library as follows, which are being downloaded and linked with Bazel Rules defined in `WORKSPACE` and `bazel/` of this repository.

* [nlohmann/units](https://github.com/nholthaus/units)
* [nholthaus/json](https://github.com/nlohmann/json)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
* [googletest](https://github.com/google/googletest)
* [eigen](https://bitbucket.org/eigen/eigen)
* [tensorflow](https://github.com/tensorflow/tensorflow)
* [pytorch](https://github.com/pytorch/pytorch)
* [opencv](https://github.com/opencv/opencv)

