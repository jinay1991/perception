///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/simulator_node.h"

#include "perception/communication/topics.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

namespace perception
{

SimulatorNode::SimulatorNode(middleware::IPubSubFactory& factory)
    : middleware::Node{"simulator_node", factory}, driver_camera_message_{}
{
}

void SimulatorNode::Init()
{
    AddPublisher<DriverCameraTopic>(
        [&driver_camera_message = driver_camera_message_] { return driver_camera_message; });
}

void SimulatorNode::ExecuteStep() {}

void SimulatorNode::Shutdown() {}

void SimulatorNode::LookStraight()
{
    driver_camera_message_ = DriverCameraMessageBuilder()
                                 .WithHeadPose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithGazePose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithEyeState(true)
                                 .Build();
}
}  // namespace perception
