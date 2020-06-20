///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/calib3d.hpp>

namespace perception
{
Camera::Camera(const std::string& source)
    : source_{source}, capture_device_{source_}, calibration_{"data/camera_calibration", 9, 6}
{
}

void Camera::Init()
{
    Calibrate();
}

void Camera::Step()
{
    Image image{};
    capture_device_ >> image;

    Image undistorted_image{};
    cv::undistort(image, undistorted_image, calibration_.GetCameraMatrix(), calibration_.GetDistanceCoeffs());

    camera_message_.calibration_params.intrinsic = calibration_.GetCameraMatrix();
    camera_message_.calibration_params.extrinsic = calibration_.GetDistanceCoeffs();
    camera_message_.image = image;
    camera_message_.undistorted_image = undistorted_image;
}

void Camera::Shutdown()
{
    calibration_.Shutdown();
    capture_device_.release();
}

void Camera::Calibrate()
{
    calibration_.Init();
    calibration_.Execute();
}

void Camera::SetSource(const std::string source)
{
    capture_device_.open(source);
    ASSERT_CHECK(capture_device_.isOpened());

    LOG(INFO) << "Reading " << source << " source.";
}

CameraMessage Camera::GetCameraMessage() const
{
    return camera_message_;
}
}  // namespace perception
