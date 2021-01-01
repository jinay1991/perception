///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/test/support/driver_consumer_node.h"

#include "perception/communication/topics.h"

namespace perception
{

DriverConsumerNode::DriverConsumerNode(middleware::IPubSubFactory& factory)
    : middleware::Node{"driver_consumer_node", factory}, fatigue_message_{}, visual_attention_message_{}
{
}

void DriverConsumerNode::Init()
{
    AddSubscriber<FatigueTopic>(
        [&fatigue_message = fatigue_message_](const auto& message) { fatigue_message = message; });
    AddSubscriber<VisualAttentionTopic>([&visual_attention_message = visual_attention_message_](const auto& message) {
        visual_attention_message = message;
    });
}

void DriverConsumerNode::ExecuteStep() {}

void DriverConsumerNode::Shutdown() {}

const FatigueMessage& DriverConsumerNode::GetFatigueMessage() const
{
    return fatigue_message_;
}

const VisualAttentionMessage& DriverConsumerNode::GetVisualAttentionMessage() const
{
    return visual_attention_message_;
}

}  // namespace perception
