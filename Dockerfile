FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && apt-get autoremove -y

# Installation of general dependencies
RUN apt-get install -y build-essential gcc g++ lcov make cmake
RUN apt-get install -y openjdk-11-jdk openjdk-11-jre
RUN apt-get install -y libtool clang-format-6.0
RUN apt-get install -y git git-lfs curl
RUN apt-get install -y wget
RUN apt-get install -y libuv1-dev libssl-dev

# Installation of dependencies to Doxygen
RUN apt-get install -y doxygen graphviz plantuml

# Installation of static code analysis
RUN apt-get install -y cppcheck python python-pygments clang-tidy-6.0

# Installation of Bazel Package
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add -
RUN apt-get update && apt-get install -y bazel

# Installation of Bazel Tools
RUN wget https://github.com/bazelbuild/buildtools/releases/download/0.29.0/buildifier
RUN chmod +x buildifier
RUN mv buildifier /usr/bin

# Installation of dependencies to OpenCV
RUN apt-get install -y qt5-default libvtk6-dev zlib1g-dev libjpeg-dev libwebp-dev
RUN apt-get install -y libpng-dev libtiff5-dev libopenexr-dev libgdal-dev libavresample-dev
RUN apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev
RUN apt-get install -y libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev
RUN apt-get install -y libopencore-amrwb-dev libv4l-dev libxine2-dev libtbb-dev libeigen3-dev
RUN apt-get install -y python3-dev python3-tk python3-numpy python3-pip
RUN apt-get install -y ant default-jdk

RUN python3 -m pip install -U pip
RUN python3 -m pip install -U numpy tensorflow matplotlib pandas scikit-image sklearn

# Installation of OpenCV 4.2.0
ENV OPENCV_VERSION="4.2.0"

RUN wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip && \
    unzip ${OPENCV_VERSION}.zip && rm -rf ${OPENCV_VERSION}.zip && \
    mkdir -p opencv-${OPENCV_VERSION}/build
RUN cd opencv-${OPENCV_VERSION}/build && \
    cmake -DBUILD_TESTS=OFF -DBUILT_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DWITH_LIBV4L=ON -DWITH_OPENGL=ON .. && \
    make -j8 && \
    make install && \
    cd -
RUN rm -rf opencv-${OPENCV_VERSION}

# cleanup
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
RUN apt-get autoremove && apt-get autoclean
