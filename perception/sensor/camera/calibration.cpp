///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/calibration.h"

#include <opencv4/opencv2/calib3d/calib3d.hpp>

namespace perception
{
namespace sensor
{
namespace camera
{

Calibration::Calibration() : root_mean_square_{}, matrix_{}, distance_{}, rotation_{}, translation_{} {}

void Calibration::Execute() {}

}  // namespace camera
}  // namespace sensor
}  // namespace perception
