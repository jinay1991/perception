///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_SIMULATOR_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_SIMULATOR_H

#include "middleware/lifecycle/node.h"
#include "perception/datatypes/driver.h"

namespace perception
{
class SimulatorNode : public middleware::Node
{
  public:
    explicit SimulatorNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

    void LookStraight();

  private:
    DriverCameraMessage driver_camera_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_SIMULATOR_H
