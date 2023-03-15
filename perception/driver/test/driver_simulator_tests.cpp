///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/test/support/driver_simulator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

class DriverSimulatorFixture : public ::testing::Test
{
  public:
    DriverSimulatorFixture() : simulator_{} {}

  protected:
    void RunOnce() { simulator_.Step(); }

    void RunForDuration(const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kMaxCycleDuration)
        {
            RunOnce();
        }
    }

    DriverSimulator& GetSimulator() { return simulator_; }

    const DriverCameraMessage& GetDriverCameraMessage() const { return simulator_.GetDriverCameraMessage(); }

  private:
    DriverSimulator simulator_;
};

TEST_F(DriverSimulatorFixture, Initialization_GivenDriverSimulator_ExpectDefaultDriverCameraMessage)
{
    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                AllOf(Field(&DriverCameraMessage::face_tracking,
                            AllOf(Field(&FaceTracking::face_visible, true),
                                  Field(&FaceTracking::eye_visible, true),
                                  Field(&FaceTracking::eye_blink_rate, kMaxEyeBlinkRate),
                                  Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening))),
                      Field(&DriverCameraMessage::head_tracking,
                            AllOf(Field(&HeadTracking::yaw, 0.0_rad),
                                  Field(&HeadTracking::pitch, 0.0_rad),
                                  Field(&HeadTracking::roll, 0.0_rad))),
                      Field(&DriverCameraMessage::gaze_tracking,
                            AllOf(Field(&GazeTracking::yaw, 0.0_rad),
                                  Field(&GazeTracking::pitch, 0.0_rad),
                                  Field(&GazeTracking::roll, 0.0_rad)))));
}

TEST_F(DriverSimulatorFixture, ShowFace_GivenDriverSimulator_ExpectVisibleFace)
{
    // Given
    GetSimulator().ShowFace();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::face_visible, true)));
}

TEST_F(DriverSimulatorFixture, HideFace_GivenDriverSimulator_ExpectVisibleFace)
{
    // Given
    GetSimulator().HideFace();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::face_visible, false)));
}

TEST_F(DriverSimulatorFixture, CloseEyes_GivenDriverSimulator_ExpectClosedEyes)
{
    // Given
    GetSimulator().CloseEyes();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking,
                      AllOf(Field(&FaceTracking::eye_lid_opening, kMinEyeLidOpening),
                            Field(&FaceTracking::eye_visible, true))));
}

TEST_F(DriverSimulatorFixture, OpenEyes_GivenDriverSimulator_ExpectOpenedEyes)
{
    // Given
    GetSimulator().OpenEyes();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking,
                      AllOf(Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening),
                            Field(&FaceTracking::eye_visible, true))));
}

TEST_F(DriverSimulatorFixture, BlinkEyes_GivenTypicalBlinkRate_ExpectUpdatedEyesBlinkRate)
{
    // Given
    const units::frequency::hertz_t blink_rate = 10_Hz;
    GetSimulator().BlinkEyes(blink_rate);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_blink_rate, blink_rate)));
}

TEST_F(DriverSimulatorFixture, ToggleEyes_GivenEyesOpen_ExpectToggleEyes)
{
    // Given
    RunOnce();  // toggles to open eyes
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));

    // When
    RunForDuration(2'150ms);  // toggles to close eyes

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMinEyeLidOpening)));
}

TEST_F(DriverSimulatorFixture, ToggleEyes_GivenEyesClosed_ExpectToggleEyes)
{
    // Given
    RunForDuration(2'150ms);  // toggles to close eyes
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMinEyeLidOpening)));

    // When
    RunForDuration(2'150ms);  // toggles to open eyes

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));
}

TEST_F(DriverSimulatorFixture, ToggleEyes_GivenEyesClosedAfterSeveralBlinks_ExpectToggleEyes)
{
    // Given
    RunForDuration(2'150ms);  // toggles to close eyes
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMinEyeLidOpening)));

    // When
    RunForDuration(2'150ms);  // toggles to open eyes

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));
}

TEST_F(DriverSimulatorFixture, LookLeft_GivenDriverSimulator_ExpectMaxPositiveHeadTrackingYaw)
{
    // Given
    GetSimulator().LookLeft();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, -kMinHeadPoseYaw)));
}

TEST_F(DriverSimulatorFixture, LookRight_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingYaw)
{
    // Given
    GetSimulator().LookRight();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, kMaxHeadPoseYaw)));
}

TEST_F(DriverSimulatorFixture, LookStraight_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingRoll)
{
    // Given
    GetSimulator().LookStraight();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking,
                      AllOf(Field(&HeadTracking::yaw, 0.0_rad),
                            Field(&HeadTracking::pitch, 0.0_rad),
                            Field(&HeadTracking::roll, 0.0_rad))));
}

TEST_F(DriverSimulatorFixture, LookDown_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingPitch)
{
    // Given
    GetSimulator().LookDown();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, -kMinHeadPosePitch)));
}

TEST_F(DriverSimulatorFixture, LookUp_GivenDriverSimulator_ExpectMaxPositiveHeadTrackingRoll)
{
    // Given
    GetSimulator().LookUp();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, kMaxHeadPosePitch)));
}

TEST_F(DriverSimulatorFixture, MoveHeadUp_GivenTypicalDeltaPitch_ExpectMovedHeadUp)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().MoveHeadUp(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, delta_pitch)));
}

TEST_F(DriverSimulatorFixture, MoveHeadDown_GivenTypicalDeltaPitch_ExpectMovedHeadDown)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().MoveHeadDown(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, -delta_pitch)));
}

TEST_F(DriverSimulatorFixture, MoveHeadLeft_GivenTypicalDeltaYaw_ExpectMovedHeadLeft)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveHeadLeft(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, -delta_yaw)));
}

TEST_F(DriverSimulatorFixture, MoveHeadRight_GivenTypicalDeltaYaw_ExpectMovedHeadRight)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveHeadRight(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, delta_yaw)));
}

TEST_F(DriverSimulatorFixture, TiltHeadLeft_GivenTypicalDeltaRoll_ExpectTiltedHeadLeft)
{
    // Given
    const units::angle::radian_t delta_roll = 10.0_deg;
    GetSimulator().TiltHeadLeft(delta_roll);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, -delta_roll)));
}

TEST_F(DriverSimulatorFixture, TiltHeadLeft_GivenTypicalDeltaRoll_ExpectTiltedHeadRight)
{
    // Given
    const units::angle::radian_t delta_roll = 10.0_deg;
    GetSimulator().TiltHeadRight(delta_roll);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, delta_roll)));
}

TEST_F(DriverSimulatorFixture, MoveGazeUp_GivenTypicalDeltaPitch_ExpectMovedGazeUp)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().MoveGazeUp(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::gaze_tracking, Field(&GazeTracking::pitch, delta_pitch)));
}

TEST_F(DriverSimulatorFixture, MoveGazeDown_GivenTypicalDeltaPitch_ExpectMovedGazeDown)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().MoveGazeDown(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::gaze_tracking, Field(&GazeTracking::pitch, -delta_pitch)));
}

TEST_F(DriverSimulatorFixture, MoveGazeLeft_GivenTypicalDeltaYaw_ExpectMovedGazeLeft)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveGazeLeft(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::gaze_tracking, Field(&GazeTracking::yaw, -delta_yaw)));
}

TEST_F(DriverSimulatorFixture, MoveGazeRight_GivenTypicalDeltaYaw_ExpectMovedGazeRight)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveGazeRight(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::gaze_tracking, Field(&GazeTracking::yaw, delta_yaw)));
}
}  // namespace
}  // namespace driver
}  // namespace perception
