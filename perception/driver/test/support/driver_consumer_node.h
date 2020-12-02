///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CONSUMER_NODE_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CONSUMER_NODE_H

#include "middleware/lifecycle/node.h"
#include "perception/datatypes/driver.h"

namespace perception
{

class DriverConsumerNode : public middleware::Node
{
  public:
    explicit DriverConsumerNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

    const FatigueMessage& GetFatigueMessage() const;
    const VisualAttentionMessage& GetVisualAttentionMessage() const;

  private:
    FatigueMessage fatigue_message_;
    VisualAttentionMessage visual_attention_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CONSUMER_NODE_H
