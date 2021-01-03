///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/node/driver_node.h"

#include "middleware/lifecycle/node.h"
#include "perception/communication/topics.h"

namespace perception
{
DriverNode::DriverNode(middleware::IPubSubFactory& factory) : middleware::Node{"driver_node", factory}, driver_{} {}

void DriverNode::Init()
{
    AddSubscriber<DriverCameraTopic>([&driver = driver_](const DriverCameraMessage& driver_camera_message) {
        driver.ProcessDriverCameraMessage(driver_camera_message);
    });

    AddPublisher<FatigueTopic>([&driver = driver_] { return driver.GetFatigueMessage(); });
    AddPublisher<VisualAttentionTopic>([&driver = driver_] { return driver.GetVisualAttentionMessage(); });
}

void DriverNode::ExecuteStep()
{
    driver_.Step();
}

void DriverNode::Shutdown()
{
}

}  // namespace perception
