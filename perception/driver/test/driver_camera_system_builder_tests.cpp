///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/driver_camera_system_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using namespace units::literals;

TEST(DriverCameraSystemBuilderTest, DefaultConstructor_ExpectDefaultDriverCameraSystem)
{
    // Given
    const DriverCameraSystem driver_camera_system{};

    // When
    const auto result = DriverCameraSystemBuilder().Build();

    // Then
    EXPECT_EQ(result, driver_camera_system);
}

TEST(DriverCameraSystemBuilderTest, WithFaceTracking_GivenTypicalFaceTracking_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const FaceTracking face_tracking{true, 10.0_mm, 2.0_Hz};

    // When
    const auto result = DriverCameraSystemBuilder().WithFaceTracking(face_tracking).Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}

TEST(DriverCameraSystemBuilderTest, WithHeadTracking_GivenTypicalHeadTracking_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemBuilder().WithHeadTracking(head_tracking).Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraSystemBuilderTest, WithGazeTracking_GivenTypicalGazeTracking_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemBuilder().WithGazeTracking(gaze_tracking).Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraSystemBuilderTest, WithHeadPose_GivenTypicalHeadPose_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result =
        DriverCameraSystemBuilder().WithHeadPose(head_tracking.yaw, head_tracking.pitch, head_tracking.roll).Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraSystemBuilderTest, WithGazePose_GivenTypicalGazePose_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result =
        DriverCameraSystemBuilder().WithGazePose(gaze_tracking.yaw, gaze_tracking.pitch, gaze_tracking.roll).Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraSystemBuilderTest, WithEyesState_GivenTypicalEyesState_ExpectUpdatedDriverCameraSystem)
{
    // Given
    const FaceTracking face_tracking{true, 10.0_mm, 2.0_Hz};

    // When
    const auto result =
        DriverCameraSystemBuilder()
            .WithEyeState(face_tracking.eye_visibility, face_tracking.eye_lid_opening, face_tracking.eye_blink_rate)
            .Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}
}  // namespace
}  // namespace perception
