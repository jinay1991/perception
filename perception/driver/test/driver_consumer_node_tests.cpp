///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_publisher.h"
#include "perception/communication/topics.h"
#include "perception/driver/test/support/driver_consumer_node.h"
#include "perception/driver/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

class DriverConsumerNodeFixture : public ::testing::Test
{
  public:
    DriverConsumerNodeFixture()
        : factory_{},
          consumer_{factory_},
          fatigue_publisher_{"fatigue_publisher", factory_},
          visual_attention_publisher_{"visual_attention_publisher", factory_}
    {
    }

  protected:
    void SetUp() override
    {
        consumer_.Init();
        fatigue_publisher_.Init();
        visual_attention_publisher_.Init();
    }

    void TearDown() override
    {
        consumer_.Shutdown();
        fatigue_publisher_.Shutdown();
        visual_attention_publisher_.Shutdown();
    }

    void RunOnce()
    {
        fatigue_publisher_.Step();
        visual_attention_publisher_.Step();
        consumer_.Step();
    }

    void PublishFatigueMessage(const FatigueMessage& fatigue_message)
    {
        fatigue_publisher_.PublishInput(fatigue_message);
    }

    void PublishVisualAttentionMessage(const VisualAttentionMessage& visual_attention_message)
    {
        visual_attention_publisher_.PublishInput(visual_attention_message);
    }

    const FatigueMessage& GetFatigueMessage() const { return consumer_.GetFatigueMessage(); }
    const VisualAttentionMessage& GetVisualAttentionMessage() const { return consumer_.GetVisualAttentionMessage(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    DriverConsumerNode consumer_;
    middleware::SingleTopicPublisher<FatigueTopic> fatigue_publisher_;
    middleware::SingleTopicPublisher<VisualAttentionTopic> visual_attention_publisher_;
};

TEST_F(DriverConsumerNodeFixture, GetFatigueMessage_GivenTypicalFatigueMessage_ExpectReceivedSame)
{
    // Given
    FatigueMessage fatigue_message{};
    fatigue_message.eye_state = EyeState::kEyesClosed;
    PublishFatigueMessage(fatigue_message);

    // When
    RunOnce();

    // Then
    EXPECT_EQ(GetFatigueMessage(), fatigue_message);
}

TEST_F(DriverConsumerNodeFixture, GetVisualAttentionMessage_GivenTypicalVisualAttentionMessage_ExpectReceivedSame)
{
    // Given
    VisualAttentionMessage visual_attention_message{};
    visual_attention_message.attention_state = AttentionState::kAttentive;
    PublishVisualAttentionMessage(visual_attention_message);

    // When
    RunOnce();

    // Then
    EXPECT_EQ(GetVisualAttentionMessage(), visual_attention_message);
}
}  // namespace
}  // namespace perception
