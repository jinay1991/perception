FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && apt-get autoremove -y

# Installation of general dependencies
RUN apt-get install -y build-essential gcc g++ gdb lcov make cmake
RUN apt-get install -y libtool clang-format clang-tidy
RUN apt-get install -y git git-lfs
RUN apt-get install -y wget curl vim
RUN apt-get install -y libncurses5

# Installation of dependencies to Doxygen
RUN apt-get install -y doxygen graphviz plantuml

# Installation of static code analysis
RUN apt-get install -y cppcheck python python-pygments

# Installatin of dependencies to Bazel
RUN apt-get install -y openjdk-11-jdk openjdk-11-jre

# Installation of Bazel Package
RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add -
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt-get update && apt-get install -y bazel
RUN echo "source /etc/bash_completion.d/bazel" >> ~/.bashrc

# Installation of Bazel Tools
RUN wget https://github.com/bazelbuild/buildtools/releases/download/3.4.0/buildifier
RUN chmod +x buildifier
RUN mv buildifier /usr/bin

# Installation of dependencies to OpenCV
RUN apt-get install -y qt5-default libvtk6-dev zlib1g-dev libjpeg-dev libwebp-dev
RUN apt-get install -y libpng-dev libtiff5-dev libopenexr-dev libgdal-dev libavresample-dev
RUN apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev
RUN apt-get install -y libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev 
RUN apt-get install -y libgtkglext1 libgtkglext1-dev libgtk2.0-dev pkg-config
RUN apt-get install -y libopencore-amrwb-dev libv4l-dev libxine2-dev libtbb-dev libeigen3-dev
RUN apt-get install -y python3-dev python3-tk python3-numpy python3-pip
RUN apt-get install -y ant default-jdk

RUN python3 -m pip install -U pip
RUN python3 -m pip install -U numpy tensorflow matplotlib pandas scikit-image sklearn

# Installation of OpenCV 4.4.0
ENV OPENCV_VERSION="4.4.0"

RUN wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip && \
    unzip ${OPENCV_VERSION}.zip && rm -rf ${OPENCV_VERSION}.zip && \
    mkdir -p opencv-${OPENCV_VERSION}/build
RUN cd opencv-${OPENCV_VERSION}/build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILT_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DWITH_LIBV4L=ON -DWITH_OPENGL=ON .. && \
    make -j8 && \
    make install && \
    cd -
RUN rm -rf opencv-${OPENCV_VERSION}

# cleanup
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
RUN apt-get autoremove && apt-get autoclean
