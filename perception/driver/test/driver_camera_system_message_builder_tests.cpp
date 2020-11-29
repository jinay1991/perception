///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/builders/driver_camera_system_message_builder.h"
#include "perception/driver/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{

TEST(DriverCameraSystemMessageBuilderTest, DefaultConstructor_ExpectDefaultDriverCameraSystemMessage)
{
    // Given
    const DriverCameraSystemMessage driver_camera_system_message{};

    // When
    const auto result = DriverCameraSystemMessageBuilder().Build();

    // Then
    EXPECT_EQ(result, driver_camera_system_message);
}

TEST(DriverCameraSystemMessageBuilderTest, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();

    // When
    const auto result = DriverCameraSystemMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_EQ(result.time_point, time_point);
}

TEST(DriverCameraSystemMessageBuilderTest,
     WithFaceTracking_GivenTypicalFaceTracking_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const FaceTracking face_tracking{true, 10.0_mm, 2.0_Hz};

    // When
    const auto result = DriverCameraSystemMessageBuilder().WithFaceTracking(face_tracking).Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}

TEST(DriverCameraSystemMessageBuilderTest,
     WithHeadTracking_GivenTypicalHeadTracking_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemMessageBuilder().WithHeadTracking(head_tracking).Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraSystemMessageBuilderTest,
     WithGazeTracking_GivenTypicalGazeTracking_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemMessageBuilder().WithGazeTracking(gaze_tracking).Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraSystemMessageBuilderTest, WithHeadPose_GivenTypicalHeadPose_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemMessageBuilder()
                            .WithHeadPose(head_tracking.yaw, head_tracking.pitch, head_tracking.roll)
                            .Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraSystemMessageBuilderTest, WithGazePose_GivenTypicalGazePose_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraSystemMessageBuilder()
                            .WithGazePose(gaze_tracking.yaw, gaze_tracking.pitch, gaze_tracking.roll)
                            .Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraSystemMessageBuilderTest, WithEyesState_GivenTypicalEyesState_ExpectUpdatedDriverCameraSystemMessage)
{
    // Given
    const FaceTracking face_tracking{true, 10.0_mm, 2.0_Hz};

    // When
    const auto result =
        DriverCameraSystemMessageBuilder()
            .WithEyeState(face_tracking.eye_visibility, face_tracking.eye_lid_opening, face_tracking.eye_blink_rate)
            .Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}
}  // namespace
}  // namespace perception
