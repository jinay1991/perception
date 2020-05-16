///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_H_
#define PERCEPTION_SENSOR_CAMERA_CAMERA_H_

#include "perception/datatypes/camera.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <string>

namespace perception
{

class Camera
{
  public:
    Camera();

    virtual void Init();
    virtual void Execute();
    virtual void Shutdown();

    virtual void SetSource(const std::string source);

    virtual Image GetImage() const;

  private:
    /// @brief Capture Device
    cv::VideoCapture capture_device_;

    /// @brief Camera Source
    /// @note Provide {} (i.e. empty string) to use camera inputs or
    /// provide video path to use video as input
    std::string source_;

    /// @brief Calibration Parameters (intrinsic/extrinsic params)
    CalibrationParams calibration_params_;

    /// @brief Last updated frame (i.e. image) from the Video/Sensor
    Image image_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_H_
