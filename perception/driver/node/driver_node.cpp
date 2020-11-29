///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/node/driver_node.h"

#include "middleware/lifecycle/node.h"
#include "perception/communication/topics.h"

namespace perception
{
DriverNode::DriverNode(middleware::IPubSubFactory& factory) : middleware::Node{"driver_node", factory}, driver_{} {}

void DriverNode::Init()
{
    AddSubscriber<DriverCameraSystemTopic>(
        [&driver = driver_](const DriverCameraSystemMessage& driver_camera_system_message) {
            driver.ProcessDriverCameraSystemMessage(driver_camera_system_message);
        });

    AddPublisher<FatigueTopic>([&driver = driver_] { return driver.GetFatigueMessage(); });
    AddPublisher<VisualAttentionTopic>([&driver = driver_] { return driver.GetVisualAttentionMessage(); });
}

void DriverNode::ExecuteStep()
{
    driver_.ExecuteStep();
}

void DriverNode::Shutdown()
{
    driver_.Shutdown();
}

}  // namespace perception
