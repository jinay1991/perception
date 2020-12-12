///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_SENSOR_DRIVER_CAMERA_NODE_DRIVER_CAMERA_NODE_H
#define PERCEPTION_SENSOR_DRIVER_CAMERA_NODE_DRIVER_CAMERA_NODE_H

#include "middleware/lifecycle/node.h"
#include "perception/sensor/driver_camera/driver_camera.h"

namespace perception
{

/// @brief Driver Camera Node
class DriverCameraNode final : public middleware::Node
{
  public:
    /// @brief Constructor.
    /// @param factory[in] Middleware Publisher/Subscriber Factory
    explicit DriverCameraNode(middleware::IPubSubFactory& factory);

    /// @brief Initialize Driver Camera Node
    void Init() override;

    /// @brief Execute single step for Driver Camera Node
    void ExecuteStep() override;

    /// @brief Shutdown/Deinitialize Driver Camera Node
    void Shutdown() override;

  private:
    /// @brief Instance of Driver Camera
    DriverCamera driver_camera_;
};
}  // namespace perception
#endif  /// PERCEPTION_SENSOR_DRIVER_CAMERA_NODE_DRIVER_CAMERA_NODE_H
