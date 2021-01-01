///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/driver.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::Field;

class DriverFixture : public ::testing::Test
{
  public:
    DriverFixture() : driver_{} {}

  protected:
    void SetUp() override { driver_.Init(); }
    void TearDown() override { driver_.Shutdown(); }
    void RunOnce() { driver_.Step(); }

    void UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
    {
        driver_.ProcessDriverCameraMessage(driver_camera_message);
    }

    const FatigueMessage& GetFatigueMessage() const { return driver_.GetFatigueMessage(); }
    const VisualAttentionMessage& GetVisualAttentionMessage() const { return driver_.GetVisualAttentionMessage(); }

  private:
    Driver driver_;
};

TEST_F(DriverFixture, Driver_GivenTypicalDriverCameraMessage_ExpectUpdatedFatigue)
{
    // Given
    const DriverCameraMessage driver_camera_message =
        DriverCameraMessageBuilder().WithEyeState(true, true, 0.0_mm, 1.0_Hz).Build();
    UpdateDriverCameraMessage(driver_camera_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, EyeState::kEyesClosed));
}

TEST_F(DriverFixture, Driver_GivenTypicalDriverCameraMessage_ExpectUpdatedVisualAttention)
{
    // Given
    const DriverCameraMessage driver_camera_message =
        DriverCameraMessageBuilder().WithHeadPose(0.10_rad, 0.11_rad, 0.0_rad).Build();
    UpdateDriverCameraMessage(driver_camera_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetVisualAttentionMessage(), Field(&VisualAttentionMessage::attention_state, AttentionState::kInvalid));
}
}  // namespace
}  // namespace perception
