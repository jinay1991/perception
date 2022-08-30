///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/driver.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::Field;

class DriverFixture : public ::testing::Test
{
  public:
    DriverFixture() : driver_{} {}

  protected:
    void RunOnce() { driver_.Step(); }

    void RunForDuration(const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kMaxCycleDuration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += step)
        {
            RunOnce();
        }
    }

    void UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
    {
        driver_.UpdateDriverCameraMessage(driver_camera_message);
    }

    const FatigueMessage& GetFatigueMessage() const { return driver_.GetFatigueMessage(); }
    const DistractionMessage& GetDistractionMessage() const { return driver_.GetDistractionMessage(); }
    const ActivityMessage& GetActivityMessage() const { return driver_.GetActivityMessage(); }
    const ResponsivenessMessage& GetResponsivenessMessage() const { return driver_.GetResponsivenessMessage(); }
    RiskAssessmentState GetRiskAssessmentState() const { return driver_.GetRiskAssessmentState(); }

    const DriverMessage& GetDriverMessage() const { return driver_.GetDriverMessage(); }

  private:
    Driver driver_;
};

TEST_F(DriverFixture, Driver_GivenTypicalDriverCameraMessage_ExpectUpdatedMessages)
{
    // Given
    const DriverCameraMessage driver_camera_message = test::support::DriverCameraMessageBuilder()
                                                          .WithEyeState(true, true, kMinEyeLidOpening, kMaxEyeBlinkRate)
                                                          .Build();
    UpdateDriverCameraMessage(driver_camera_message);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::state, FatigueState::kAwake));
    EXPECT_THAT(GetDistractionMessage(), Field(&DistractionMessage::state, DistractionState::kNotDistracted));
    EXPECT_THAT(GetActivityMessage(), Field(&ActivityMessage::state, ActivityState::kNotAvailable));
    EXPECT_THAT(GetResponsivenessMessage(), Field(&ResponsivenessMessage::state, ResponsivenessState::kResponsive));
    EXPECT_THAT(GetRiskAssessmentState(), RiskAssessmentState::kNone);
    EXPECT_THAT(
        GetDriverMessage(),
        AllOf(Field(&DriverMessage::fatigue, Field(&FatigueMessage::state, FatigueState::kAwake)),
              Field(&DriverMessage::distraction, Field(&DistractionMessage::state, DistractionState::kNotDistracted)),
              Field(&DriverMessage::activity, Field(&ActivityMessage::state, ActivityState::kNotAvailable)),
              Field(&DriverMessage::responsiveness,
                    Field(&ResponsivenessMessage::state, ResponsivenessState::kResponsive))));
}

TEST_F(DriverFixture, Driver_GivenSlowBlinkRate_ExpectDriverDrowsy)
{
    // Given
    const DriverCameraMessage driver_camera_message = test::support::DriverCameraMessageBuilder()
                                                          .WithEyeState(true, true, kMinEyeLidOpening, kMinEyeBlinkRate)
                                                          .Build();
    UpdateDriverCameraMessage(driver_camera_message);

    // When
    RunForDuration(35s);

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::state, FatigueState::kQuestionable));

    // When
    RunForDuration(35s);

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::state, FatigueState::kDrowsy));
}

}  // namespace
}  // namespace driver
}  // namespace perception
