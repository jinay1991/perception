///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>

namespace perception
{
Camera::Camera()
    : source_{"data/Megamind.avi"}, capture_device_{source_}, image_{}, calibration_{"data/camera_calibration", 9, 6}
{
}

void Camera::Init()
{
    calibration_.Init();

    // Self-Calibration with provided calibration data
    calibration_.Execute();
}

void Camera::Execute()
{
    capture_device_ >> image_;
}

void Camera::Shutdown()
{
    calibration_.Shutdown();
    capture_device_.release();
}

void Camera::SetSource(const std::string source)
{
    capture_device_.open(source);
    ASSERT_CHECK(capture_device_.isOpened());

    LOG(INFO) << "Reading " << source << " source (camera).";
}

Image Camera::GetImage() const
{
    return image_;
}

Image Camera::GetUndistortedImage() const
{
    Image undistorted_image{};
    cv::undistort(image_, undistorted_image, calibration_.GetCameraMatrix(), calibration_.GetDistanceCoeffs());
    return undistorted_image;
}

}  // namespace perception
