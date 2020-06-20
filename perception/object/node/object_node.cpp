///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/node/object_node.h"

#include "perception/communication/topics.h"

namespace perception
{
ObjectNode::ObjectNode(middleware::IPubSubFactory& factory)
    : Node{"object_node", factory}, object_message_{}, camera_message_{}
{
}

void ObjectNode::Init()
{
    AddSubscriber<CameraTopic>([this](const auto& data) { camera_message_ = data; });
    AddPublisher<ObjectTopic>([this]() { return object_message_; });
}

void ObjectNode::ExecuteStep() {}

void ObjectNode::Shutdown() {}

}  // namespace perception