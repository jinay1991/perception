///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/support/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/driver/test/support/driver_simulator_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using ::testing::AllOf;
using ::testing::Field;

constexpr std::chrono::milliseconds kAssumedCycleDuration{40ms};

class DriverSimulatorNodeFixture : public ::testing::Test
{
  public:
    DriverSimulatorNodeFixture()
        : factory_{}, simulator_{factory_}, driver_camera_subscriber_{"driver_camera_subscriber", factory_}
    {
    }

  protected:
    void SetUp() override
    {
        simulator_.Init();
        driver_camera_subscriber_.Init();
    }

    void TearDown() override
    {
        simulator_.Shutdown();
        driver_camera_subscriber_.Shutdown();
    }

    void RunOnce()
    {
        simulator_.Step();
        driver_camera_subscriber_.Step();
    }

    void RunForDuration(const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kAssumedCycleDuration)
        {
            RunOnce();
        }
    }

    DriverSimulatorNode& GetSimulator() { return simulator_; }

    DriverCameraMessage GetDriverCameraMessage() const { return driver_camera_subscriber_.GetSample(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    DriverSimulatorNode simulator_;
    middleware::SingleTopicSubscriber<DriverCameraTopic> driver_camera_subscriber_;
};

TEST_F(DriverSimulatorNodeFixture, Initialization_GivenDriverSimulator_ExpectDefaultDriverCameraMessage)
{
    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                AllOf(Field(&DriverCameraMessage::face_tracking,
                            AllOf(Field(&FaceTracking::face_visibility, true),
                                  Field(&FaceTracking::eye_visibility, true),
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

TEST_F(DriverSimulatorNodeFixture, ShowFace_GivenDriverSimulator_ExpectVisibleFace)
{
    // Given
    GetSimulator().ShowFace();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::face_visibility, true)));
}

TEST_F(DriverSimulatorNodeFixture, HideFace_GivenDriverSimulator_ExpectVisibleFace)
{
    // Given
    GetSimulator().HideFace();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::face_visibility, false)));
}

TEST_F(DriverSimulatorNodeFixture, CloseEyes_GivenDriverSimulator_ExpectClosedEyes)
{
    // Given
    GetSimulator().CloseEyes();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(
        GetDriverCameraMessage(),
        Field(&DriverCameraMessage::face_tracking,
              AllOf(Field(&FaceTracking::eye_lid_opening, 0.0_mm), Field(&FaceTracking::eye_visibility, true))));
}

TEST_F(DriverSimulatorNodeFixture, OpenEyes_GivenDriverSimulator_ExpectOpenedEyes)
{
    // Given
    GetSimulator().OpenEyes();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking,
                      AllOf(Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening),
                            Field(&FaceTracking::eye_visibility, true))));
}

TEST_F(DriverSimulatorNodeFixture, BlinkEyes_GivenTypicalBlinkRate_ExpectUpdatedEyesBlinkRate)
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

TEST_F(DriverSimulatorNodeFixture, ToggleEyes_GivenEyesOpen_ExpectToggleEyes)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, 0.0_mm)));
}

TEST_F(DriverSimulatorNodeFixture, ToggleEyes_GivenEyesClosed_ExpectToggleEyes)
{
    // Given
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, 0.0_mm)));

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));
}

TEST_F(DriverSimulatorNodeFixture, ToggleEyes_GivenEyesClosedAfterSeveralBlinks_ExpectToggleEyes)
{
    // Given
    RunForDuration(2 * kAssumedCycleDuration);
    ASSERT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, 0.0_mm)));

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::face_tracking, Field(&FaceTracking::eye_lid_opening, kMaxEyeLidOpening)));
}

TEST_F(DriverSimulatorNodeFixture, LookLeft_GivenDriverSimulator_ExpectMaxPositiveHeadTrackingYaw)
{
    // Given
    GetSimulator().LookLeft();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, kMaxHeadPoseYaw)));
}

TEST_F(DriverSimulatorNodeFixture, LookRight_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingYaw)
{
    // Given
    GetSimulator().LookRight();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, -kMaxHeadPoseYaw)));
}

TEST_F(DriverSimulatorNodeFixture, LookStraight_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingRoll)
{
    // Given
    GetSimulator().LookStraight();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, 0.0_rad)));
}

TEST_F(DriverSimulatorNodeFixture, LookDown_GivenDriverSimulator_ExpectMaxNegativeHeadTrackingRoll)
{
    // Given
    GetSimulator().LookDown();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, -kMaxHeadPoseRoll)));
}

TEST_F(DriverSimulatorNodeFixture, LookUp_GivenDriverSimulator_ExpectMaxPositiveHeadTrackingRoll)
{
    // Given
    GetSimulator().LookUp();

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, kMaxHeadPoseRoll)));
}

TEST_F(DriverSimulatorNodeFixture, MoveHeadUp_GivenTypicalDeltaRoll_ExpectMovedHeadUp)
{
    // Given
    const units::angle::radian_t delta_roll = 10.0_deg;
    GetSimulator().MoveHeadUp(delta_roll);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, delta_roll)));
}

TEST_F(DriverSimulatorNodeFixture, MoveHeadDown_GivenTypicalDeltaYaw_ExpectMovedHeadDown)
{
    // Given
    const units::angle::radian_t delta_roll = 10.0_deg;
    GetSimulator().MoveHeadDown(delta_roll);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::roll, -delta_roll)));
}

TEST_F(DriverSimulatorNodeFixture, MoveHeadLeft_GivenTypicalDeltaYaw_ExpectMovedHeadLeft)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveHeadLeft(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, delta_yaw)));
}

TEST_F(DriverSimulatorNodeFixture, MoveHeadRight_GivenTypicalDeltaYaw_ExpectMovedHeadRight)
{
    // Given
    const units::angle::radian_t delta_yaw = 10.0_deg;
    GetSimulator().MoveHeadRight(delta_yaw);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::yaw, -delta_yaw)));
}

TEST_F(DriverSimulatorNodeFixture, TiltHeadLeft_GivenTypicalDeltaPitch_ExpectTiltedHeadLeft)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().TiltHeadLeft(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, delta_pitch)));
}

TEST_F(DriverSimulatorNodeFixture, TiltHeadLeft_GivenTypicalDeltaPitch_ExpectTiltedHeadRight)
{
    // Given
    const units::angle::radian_t delta_pitch = 10.0_deg;
    GetSimulator().TiltHeadRight(delta_pitch);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetDriverCameraMessage(),
                Field(&DriverCameraMessage::head_tracking, Field(&HeadTracking::pitch, -delta_pitch)));
}
}  // namespace
}  // namespace perception
