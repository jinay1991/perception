///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_NODE_CAMERA_NODE_H
#define PERCEPTION_SENSOR_CAMERA_NODE_CAMERA_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/sensor/camera/camera.h"

#include <string>

namespace perception
{

/// @brief Camera Node
class CameraNode final : public middleware::Node
{
  public:
    /// @brief Constructor
    /// @param factor[in] - Middleware Publisher/Subscriber Factory
    explicit CameraNode(middleware::IPubSubFactory& factory);

    /// @brief Destructor
    ~CameraNode() = default;

    /// @brief Initialize Camera Node
    void Init() override;

    /// @brief Execute single step for Camera Node
    void ExecuteStep() override;

    /// @brief Shutdown/Deinitialize Camera Node
    void Shutdown() override;

    /// @brief Set Source (Camera/Video/Image Path)
    void SetSource(const std::string& source);

  private:
    /// @brief Initialize Publishers
    virtual void InitPublisher();

    /// @brief Source Path (Camera/Video/Image)
    std::string source_;

    /// @brief Instance of Camera Sensor
    Camera camera_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_NODE_CAMERA_NODE_H
