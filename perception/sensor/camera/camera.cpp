///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/core.hpp>

namespace perception
{
Camera::Camera() : capture_device_{0}, source_{}, calibration_params_{}, image_{} {}

void Camera::Init() {}
void Camera::Execute()
{
    capture_device_ >> image_;
}

void Camera::Shutdown()
{
    capture_device_.release();
}

void Camera::SetSource(const std::string source)
{
    capture_device_.open(source);
    ASSERT_CHECK(capture_device_.isOpened());
}

Image Camera::GetImage() const
{
    return image_;
}

}  // namespace perception
