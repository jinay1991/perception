///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/driver.h"
#include "perception/driver/test/support/builders/driver_camera_system_message_builder.h"
#include "perception/driver/test/support/operators.h"

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
    void RunOnce() { driver_.ExecuteStep(); }

    void UpdateDriverCameraSystemMessage(const DriverCameraSystemMessage& driver_camera_system_message)
    {
        driver_.ProcessDriverCameraSystemMessage(driver_camera_system_message);
    }

    const FatigueMessage& GetFatigueMessage() const { return driver_.GetFatigueMessage(); }
    const VisualAttentionMessage& GetVisualAttentionMessage() const { return driver_.GetVisualAttentionMessage(); }

  private:
    Driver driver_;
};

TEST_F(DriverFixture, Driver_GivenTypicalDriverCameraSystemMessage_ExpectUpdatedFatigue)
{
    // Given
    const DriverCameraSystemMessage driver_camera_system_message =
        DriverCameraSystemMessageBuilder().WithEyeState(true, 1.0_mm, 1.0_Hz).Build();
    UpdateDriverCameraSystemMessage(driver_camera_system_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, EyeState::kEyesClosed));
}

TEST_F(DriverFixture, Driver_GivenTypicalDriverCameraSystemMessage_ExpectUpdatedVisualAttention)
{
    // Given
    const DriverCameraSystemMessage driver_camera_system_message =
        DriverCameraSystemMessageBuilder().WithHeadPose(0.10_rad, 0.11_rad, 0.0_rad).Build();
    UpdateDriverCameraSystemMessage(driver_camera_system_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetVisualAttentionMessage(), Field(&VisualAttentionMessage::head_pose, HeadPose::kAttentive));
}
}  // namespace
}  // namespace perception
