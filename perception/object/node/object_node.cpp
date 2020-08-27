///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/node/object_node.h"

#include "perception/communication/topics.h"

namespace perception
{
ObjectNode::ObjectNode(middleware::IPubSubFactory& factory) : Node{"object_node", factory}, object_{} {}

void ObjectNode::Init()
{
    object_.Init();

    AddSubscriber<CameraTopic>([this](const auto& data) { object_.SetCameraMessage(data); });
    AddSubscriber<VehicleDynamicsTopic>([this](const auto& data) { object_.SetEgoVelocity(data.velocity); });

    AddPublisher<ObjectListTopic>([this]() { return object_.GetObjectListMessage(); });
}

void ObjectNode::ExecuteStep()
{
    object_.Step();
}

void ObjectNode::Shutdown()
{
    object_.Shutdown();
}

}  // namespace perception
