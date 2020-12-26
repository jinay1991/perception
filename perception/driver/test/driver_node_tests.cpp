///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "perception/communication/topics.h"
#include "perception/driver/node/driver_node.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"
#include "perception/driver/test/support/driver_consumer_node.h"
#include "perception/driver/test/support/driver_simulator_node.h"

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
    DriverNodeTest() : factory_{}, unit_{factory_}, consumer_{factory_}, simulator_{factory_} {}

  protected:
    void SetUp() override
    {
        simulator_.Init();
        unit_.Init();
        consumer_.Init();
    }

    void TearDown() override
    {
        simulator_.Shutdown();
        unit_.Shutdown();
        consumer_.Shutdown();
    }

    void RunOnce()
    {
        simulator_.Step();
        unit_.Step();
        consumer_.Step();
    }

    DriverSimulatorNode& GetSimulator() { return simulator_; }

    const FatigueMessage& GetFatigueMessage() const { return consumer_.GetFatigueMessage(); }
    const VisualAttentionMessage& GetVisualAttentionMessage() const { return consumer_.GetVisualAttentionMessage(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    DriverNode unit_;
    DriverConsumerNode consumer_;
    DriverSimulatorNode simulator_;
};

TEST_F(DriverNodeTest, GivenTypicalDriverCameraMessage_ExpectFatigueAndVisualAttention)
{
    // Given
    GetSimulator().ShowFace();
    GetSimulator().CloseEyes();
    GetSimulator().LookLeft();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, EyeState::kEyesClosed));
    EXPECT_THAT(GetVisualAttentionMessage(), Field(&VisualAttentionMessage::attention_state, AttentionState::kInvalid));
}
}  // namespace
}  // namespace perception
