///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H
#define PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/datatypes/camera.h"
#include "perception/sensor/camera/calibration.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <cstdint>
#include <string>

namespace perception
{
/// @brief Camera Sensor Model/Interface
class CameraNode : public middleware::Node
{
  public:
    /// @brief Constructor.
    explicit CameraNode(middleware::IPubSubFactory& factory);

    /// @brief Destructor.
    ~CameraNode() = default;

    /// @brief Initialize Camera
    void Init() override;

    /// @brief Execute Camera to collect frame/image
    void ExecuteStep() override;

    /// @brief Release resources used for Camera
    void Shutdown() override;

    /// @brief Set Camera Source (Physical Camera/Video/Image Inputs)
    /// @param source [in] - Camera Source (video/image path)
    virtual void SetSource(const std::string source);

  private:
    /// @brief Calibrates based on the provided calibration data
    void Calibrate();

    /// @brief Camera Source
    /// @note Provide {} (i.e. empty string) to use camera inputs or
    /// provide video path to use video as input
    std::string source_;

    /// @brief Capture Device
    cv::VideoCapture capture_device_;

    /// @brief Camera Message containing Image and Calibration Parameters
    CameraMessage camera_message_;

    /// @brief Provides self-calibration
    Calibration calibration_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H
