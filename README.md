# Preception

[![pipeline status](https://gitlab.com/jinay1991/perception/badges/master/pipeline.svg)](https://gitlab.com/jinay1991/perception/commits/master)
[![coverage report](https://gitlab.com/jinay1991/perception/badges/master/coverage.svg?job=code-coverage)](https://jinay1991.gitlab.io/perception/index.html)
[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://jinay1991.gitlab.io/perception/doc/html/)

[[Issue Board](https://gitlab.com/jinay1991/perception/-/boards)]

**WIP** Autonomous Driving Perception (with conjunction with Udacity Simulator) 

## Build

* Build project
    * Release `bazel build //...`
    * Debug `bazel build -c dbg //...`
* Run Unit Tests `bazel test //... --test_output=all`

## Test

* Launch Simulator 
* Run `./bazel-bin/client-app data/test_video.mp4`

![Screenshot](example/screenshot_01.png)

## Dependencies

* [Bazel](https://docs.bazel.build/versions/1.1.0/getting-started.html) 
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```

