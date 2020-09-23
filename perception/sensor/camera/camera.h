///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_H
#define PERCEPTION_SENSOR_CAMERA_CAMERA_H

#include "perception/datatypes/camera.h"
#include "perception/sensor/camera/calibration.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <string>

namespace perception
{
/// @brief Camera Sensor Model/Interface
class Camera
{
  public:
    /// @brief Constructor.
    /// @param source [in] Camera Source (Image/Video Path or 0 for Live Camera)
    explicit Camera(const std::string& source);

    /// @brief Destructor.
    ~Camera() = default;

    /// @brief Initialize Camera
    virtual void Init();

    /// @brief Execute single step (performs capture frame and updated camera message buffer)
    virtual void Step();

    /// @brief Release resources used for Camera
    virtual void Shutdown();

    /// @brief Set Camera Source (Physical Camera/Video/Image Inputs)
    /// @param source [in] Camera Source (video/image path)
    virtual void SetSource(const std::string source);

    /// @brief Provide last updated Camera Message based on the captured frame
    virtual CameraMessage GetCameraMessage() const;

  private:
    /// @brief Calibrates based on the provided calibration data
    virtual void Calibrate();

    /// @brief Camera Source
    /// @note Provide {} (i.e. empty string) to use camera inputs or
    /// provide video path to use video as input
    std::string source_;

    /// @brief Capture Device
    cv::VideoCapture capture_device_;

    /// @brief Camera Message
    CameraMessage camera_message_;

    /// @brief Provides self-calibration
    Calibration calibration_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_H
