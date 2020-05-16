///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_
#define PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_

#include <opencv4/opencv2/core.hpp>

namespace perception
{
namespace sensor
{
namespace camera
{
class Calibration
{
  public:
    Calibration();

    virtual void Execute();

  private:
    cv::Mat root_mean_square_;
    cv::Mat matrix_;
    cv::Mat distance_;
    cv::Mat rotation_;
    cv::Mat translation_;
};
}  // namespace camera
}  // namespace sensor
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CALIBRATION_H_
