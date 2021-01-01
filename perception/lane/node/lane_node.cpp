///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/lane/node/lane_node.h"

#include "perception/communication/topics.h"

namespace perception
{
LaneNode::LaneNode(middleware::IPubSubFactory& factory) : Node{"lane_node", factory}, lane_message_{}, camera_message_{}
{
}

void LaneNode::Init()
{
    AddPublisher<LaneTopic>([this]() { return lane_message_; });
    AddSubscriber<CameraTopic>([this](const auto& data) { camera_message_ = data; });
}

void LaneNode::ExecuteStep() {}

void LaneNode::Shutdown() {}

}  // namespace perception
