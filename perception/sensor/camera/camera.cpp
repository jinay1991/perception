///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera.h"

#include "perception/common/logging/logging.h"

namespace perception
{
Camera::Camera() : image_{} {}

void Camera::Init() {}
void Camera::Execute() {}
void Camera::Shutdown() {}

Image Camera::GetImage() const
{
    return image_;
}

}  // namespace perception
