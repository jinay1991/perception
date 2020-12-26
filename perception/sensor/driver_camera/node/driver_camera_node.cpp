///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/sensor/driver_camera/node/driver_camera_node.h"

#include "perception/communication/topics.h"

namespace perception
{

DriverCameraNode::DriverCameraNode(middleware::IPubSubFactory& factory)
    : Node{"driver_camera_node", factory}, driver_camera_{}
{
}

void DriverCameraNode::Init()
{
    driver_camera_.Init();

    AddSubscriber<CameraTopic>([this](const auto& data) { driver_camera_.SetCameraMessage(data); });
    AddPublisher<DriverCameraTopic>([this] { return driver_camera_.GetDriverCameraMessage(); });
}

void DriverCameraNode::ExecuteStep()
{
    driver_camera_.ExecuteStep();
}

void DriverCameraNode::Shutdown()
{
    driver_camera_.Shutdown();
}

}  // namespace perception
