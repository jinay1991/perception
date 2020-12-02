///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
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
                            AllOf(Field(&FaceTracking::eye_blink_rate, 1.0_Hz),
                                  Field(&FaceTracking::eye_visibility, true),
                                  Field(&FaceTracking::eye_lid_opening, 1.0_mm))),
                      Field(&DriverCameraMessage::head_tracking,
                            AllOf(Field(&HeadTracking::yaw, 0.0_rad),
                                  Field(&HeadTracking::pitch, 0.0_rad),
                                  Field(&HeadTracking::roll, 0.0_rad))),
                      Field(&DriverCameraMessage::gaze_tracking,
                            AllOf(Field(&GazeTracking::yaw, 0.0_rad),
                                  Field(&GazeTracking::pitch, 0.0_rad),
                                  Field(&GazeTracking::roll, 0.0_rad)))));
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
