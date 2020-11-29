///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_publisher.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/driver/node/driver_node.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"
#include "perception/driver/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::Field;

class DriverNodeTest : public ::testing::Test
{
  public:
    DriverNodeTest()
        : factory_{},
          unit_{factory_},
          driver_camera_publisher_{"driver_camera_publisher", factory_},
          fatigue_subscriber_{"fatigue_subscriber", factory_},
          visual_attention_subscriber_{"visual_attention_subscriber", factory_}
    {
    }

  protected:
    void SetUp() override
    {
        driver_camera_publisher_.Init();
        unit_.Init();
        fatigue_subscriber_.Init();
        visual_attention_subscriber_.Init();
    }

    void TearDown() override
    {
        driver_camera_publisher_.Shutdown();
        unit_.Shutdown();
        fatigue_subscriber_.Shutdown();
        visual_attention_subscriber_.Shutdown();
    }

    void RunOnce()
    {
        driver_camera_publisher_.Step();
        unit_.Step();
        fatigue_subscriber_.Step();
        visual_attention_subscriber_.Step();
    }

    void PublishDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
    {
        driver_camera_publisher_.PublishInput(driver_camera_message);
    }

    FatigueMessage GetFatigueMessage() const { return fatigue_subscriber_.GetSample(); }
    VisualAttentionMessage GetVisualAttentionMessage() const { return visual_attention_subscriber_.GetSample(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    DriverNode unit_;
    middleware::SingleTopicPublisher<DriverCameraTopic> driver_camera_publisher_;
    middleware::SingleTopicSubscriber<FatigueTopic> fatigue_subscriber_;
    middleware::SingleTopicSubscriber<VisualAttentionTopic> visual_attention_subscriber_;
};

TEST_F(DriverNodeTest, GivenTypicalDriverCameraMessage_ExpectFatigueAndVisualAttention)
{
    // Given
    const DriverCameraMessage driver_camera_message =
        DriverCameraMessageBuilder().WithEyeState(true, 1.0_mm, 2.0_Hz).Build();
    PublishDriverCameraMessage(driver_camera_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, EyeState::kEyesClosed));
    EXPECT_THAT(GetVisualAttentionMessage(), Field(&VisualAttentionMessage::head_pose, HeadPose::kAttentive));
}
}  // namespace
}  // namespace perception
