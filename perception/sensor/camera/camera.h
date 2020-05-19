///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_H_
#define PERCEPTION_SENSOR_CAMERA_CAMERA_H_

#include "perception/datatypes/camera.h"
#include "perception/sensor/camera/calibration.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <cstdint>
#include <string>

namespace perception
{
/// @brief Camera Sensor Model/Interface
class Camera
{
  public:
    /// @brief Constructor.
    Camera();

    /// @brief Initialize Camera
    virtual void Init();

    /// @brief Execute Camera to collect frame/image
    virtual void Execute();

    /// @brief Release resources used for Camera
    virtual void Shutdown();

    /// @brief Set Camera Source (Physical Camera/Video/Image Inputs)
    /// @param source [in] - Camera Source (video/image path)
    virtual void SetSource(const std::string source);

    /// @brief Provides last updated frame/image
    virtual Image GetImage() const;

    /// @brief Provides last updated undistorted frame/image
    virtual Image GetUndistortedImage() const;

  private:
    /// @brief Camera Source
    /// @note Provide {} (i.e. empty string) to use camera inputs or
    /// provide video path to use video as input
    std::string source_;

    /// @brief Capture Device
    cv::VideoCapture capture_device_;

    /// @brief Last updated frame (i.e. image) from the Video/Sensor
    Image image_;

    /// @brief Provides self-calibration
    Calibration calibration_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_H_
