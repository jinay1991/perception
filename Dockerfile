FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && apt-get autoremove -y

# Installation of general dependencies
RUN apt-get install -y build-essential
RUN apt-get install -y clang-format clang-tidy clangd
RUN apt-get install -y git git-lfs vim
RUN apt-get install -y wget curl gnupg

# Installatin of dependencies to Bazel
RUN apt-get install -y openjdk-11-jdk openjdk-11-jre

# Installation of Bazel Package
RUN curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
RUN mv bazel.gpg /etc/apt/trusted.gpg.d/
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt-get update && apt-get install -y bazel
RUN echo "source /etc/bash_completion.d/bazel" >> ~/.bashrc

# Installation of Bazel Tools
RUN wget https://github.com/bazelbuild/buildtools/releases/download/3.5.0/buildifier
RUN chmod +x buildifier
RUN mv buildifier /usr/bin

# Installation of dependencies to OpenCV
RUN apt-get install -y libgtkglext1 libgtkglext1-dev libgtk-3-dev libgtk2.0-dev
RUN apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libavresample-dev libavutil-dev
RUN apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

# cleanup
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
RUN apt-get autoremove && apt-get autoclean
