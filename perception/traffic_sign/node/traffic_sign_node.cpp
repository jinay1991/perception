///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/traffic_sign/node/traffic_sign_node.h"

#include "perception/communication/topics.h"

namespace perception
{
TrafficSignNode::TrafficSignNode(middleware::IPubSubFactory& factory)
    : Node{"traffic_sign_node", factory}, traffic_sign_{}
{
}

void TrafficSignNode::Init()
{
    traffic_sign_.Init();

    AddPublisher<TrafficSignListTopic>([this]() { return traffic_sign_.GetTrafficSignListMessage(); });
    AddSubscriber<CameraTopic>([this](const auto& data) { traffic_sign_.SetCameraMessage(data); });
}

void TrafficSignNode::ExecuteStep()
{
    traffic_sign_.Step();
}

void TrafficSignNode::Shutdown() {}

}  // namespace perception
