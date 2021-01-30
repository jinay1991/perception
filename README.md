# Preception

[![pipeline status](https://gitlab.com/jinay1991/perception/badges/master/pipeline.svg)](https://gitlab.com/ad_platform/perception/commits/master)
[![coverage report](https://gitlab.com/jinay1991/perception/badges/master/coverage.svg?job=code-coverage)](https://ad_platform.gitlab.io/perception/)
[![documentation](https://img.shields.io/badge/doc-doxygen-blue.svg)](https://ad_platform.gitlab.io/perception/doc/html/)
[![static code analysis](https://img.shields.io/badge/quality-cppcheck-green.svg)](https://ad_platform.gitlab.io/perception/static_code_analysis_report/)
[![Issue Board](https://img.shields.io/badge/issue-tracker-green.svg)](https://gitlab.com/ad_platform/perception/-/boards)

**WIP** Autonomous Driving Perception (with conjunction with Udacity Simulator)

## Simulator

* Download prebuilt binaries
    * [Linux](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_linux.zip)
    * [MacOS](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_mac.zip)
    * [MacOS Catalina v10.15](https://github.com/jinay1991/motion_planning/releases/download/v1.1/term3_sim_mac_catalina.zip)
    * [Windows](https://github.com/udacity/self-driving-car-sim/releases/download/T3_v1.2/term3_sim_windows.zip)

## Build

**NOTE**: Currently due to limitation of developer environment, only Linux OS is supported. Although there is a plan in place to provide compatibility with macOS as well. 

* Build project
    * Release `bazel build //...`
    * Debug `bazel build -c dbg //...`
* Run Unit Tests `bazel test //... --test_output=all`

## Dependencies

Install all the required dependencies:

```
sudo apt-get install -y build-essential gcc g++ lcov make cmake
sudo apt-get install -y openjdk-11-jdk openjdk-11-jre
sudo apt-get install -y libtool clang-format clang-tidy clangd
sudo apt-get install -y git curl
sudo apt-get install -y wget
sudo apt-get install -y libuv1-dev libssl-dev
sudo apt-get install -y libgtkglext1 libgtkglext1-dev libgtk-3-dev libgtk2.0-dev 
sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libavresample-dev libavutil-dev
sudo apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev 
```
### TensorFlow

To build `libtensorflow_cc.so`

```bash
~/$ git clone https://github.com/tensorflow/tensorflow.git
~/$ git checkout v2.3.0
~/$ cd tensorflow
~tensorflow/$ bazel build -c opt --config=monolithic //tensorflow:libtensorflow_cc.so //tensorflow:install_headers
~tensorflow/$ cd bazel-bin/tensorflow
~tensorflow/bazel-bin/tensorflow$ mkdir -p libtensorflow_cc-2.3.0-linux/include libtensorflow_cc-2.3.0-linux/lib
~tensorflow/bazel-bin/tensorflow$ cp -R include/* libtensorflow_cc-2.3.0-linux/include 
~tensorflow/bazel-bin/tensorflow$ cp -P libtensorflow_cc.so libtensorflow_cc.so.2 libtensorflow_cc.so.2.3.0 libtensorflow_cc-2.3.0-linux/lib/
~tensorflow/bazel-bin/tensorflow$ tar cvzf libtensorflow_cc-2.3.0-linux.tar.gz libtensorflow_cc-2.3.0-linux
```

Package `libtensorflow_cc-2.3.0-linux.tar.gz` contains required tensorflow libraries.

Download pre-built binaries (Linux/macOS): https://github.com/jinay1991/perception/releases/

### TensorFlow Lite


To build `libtensorflowlite.so`

```bash
~/$ git clone https://github.com/tensorflow/tensorflow.git
~/$ git checkout v2.3.0
~/$ cd tensorflow
~tensorflow/$ bazel build -c opt --config=monolithic //tensorflow/lite:libtensorflowlite.so
~tensorflow/$ cd bazel-bin/tensorflow/lite
~tensorflow/bazel-bin/tensorflow$ mkdir -p libtensorflowlite-2.3.0-linux/include libtensorflowlite-2.3.0-linux/lib
~tensorflow/bazel-bin/tensorflow$ cp --parents -r ~tensorflow/lite/**/**/*.h libtensorflowlite-2.3.0-linux/include 
~tensorflow/bazel-bin/tensorflow$ cp -P libtensorflowlite.so libtensorflowlite-2.3.0-linux/lib/
~tensorflow/bazel-bin/tensorflow$ tar cvzf libtensorflowlite-2.3.0-linux.tar.gz libtensorflowlite-2.3.0-linux
```

Package `libtensorflowlite-2.3.0-linux.tar.gz` contains required tensorflowlite libraries.

Download pre-built binaries (Linux/macOS): https://github.com/jinay1991/perception/releases/

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
cmake -DCMAKE_INSTALL_PREFIX=../install -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_opencv_apps=OFF -DBUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release -DWITH_1394=OFF -DWITH_GSTREAMER=ON -DWITH_FFMPEG=ON -DWITH_GTK=ON .. && \
make -j8 && make install && \
cd ../install && tar cvzf libopencv_dev-4.5.0-linux.tar.gz \
```

Download pre-built binaries (Linux): https://github.com/jinay1991/perception/releases/

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
* [benchmark](https://github.com/google/benchmark)
* [glog](https://github.com/google/glog)
* [eigen](https://bitbucket.org/eigen/eigen)
* [tensorflow](https://github.com/tensorflow/tensorflow)
* [pytorch](https://github.com/pytorch/pytorch)
* [opencv](https://github.com/opencv/opencv)

## Acknowledgement


