///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace test
{
namespace support
{
namespace
{

TEST(DriverCameraMessageBuilderTest, Build_ExpectDefaultDriverCameraMessage)
{
    // Given
    constexpr DriverCameraMessage driver_camera_message{};

    // When
    const auto result = DriverCameraMessageBuilder().Build();

    // Then
    EXPECT_EQ(result, driver_camera_message);
}

TEST(DriverCameraMessageBuilderTest, WithTimePoint_GivenTypicalTimePoint_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();

    // When
    const auto result = DriverCameraMessageBuilder().WithTimePoint(time_point).Build();

    // Then
    EXPECT_EQ(result.time_point, time_point);
}

TEST(DriverCameraMessageBuilderTest, WithFaceTracking_GivenTypicalFaceTracking_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const FaceTracking face_tracking{true, true, 10.0_mm, 2.0_Hz};

    // When
    const auto result = DriverCameraMessageBuilder().WithFaceTracking(face_tracking).Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}

TEST(DriverCameraMessageBuilderTest, WithHeadTracking_GivenTypicalHeadTracking_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraMessageBuilder().WithHeadTracking(head_tracking).Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraMessageBuilderTest, WithGazeTracking_GivenTypicalGazeTracking_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result = DriverCameraMessageBuilder().WithGazeTracking(gaze_tracking).Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraMessageBuilderTest, WithHeadPose_GivenTypicalHeadPose_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result =
        DriverCameraMessageBuilder().WithHeadPose(head_tracking.yaw, head_tracking.pitch, head_tracking.roll).Build();

    // Then
    EXPECT_EQ(result.head_tracking, head_tracking);
}

TEST(DriverCameraMessageBuilderTest, WithGazePose_GivenTypicalGazePose_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, 12.0_rad};

    // When
    const auto result =
        DriverCameraMessageBuilder().WithGazePose(gaze_tracking.yaw, gaze_tracking.pitch, gaze_tracking.roll).Build();

    // Then
    EXPECT_EQ(result.gaze_tracking, gaze_tracking);
}

TEST(DriverCameraMessageBuilderTest, WithEyesState_GivenTypicalEyesState_ExpectUpdatedDriverCameraMessage)
{
    // Given
    const FaceTracking face_tracking{true, true, 10.0_mm, 2.0_Hz};

    // When
    const auto result = DriverCameraMessageBuilder()
                            .WithEyeState(face_tracking.face_visible,
                                          face_tracking.eye_visible,
                                          face_tracking.eye_lid_opening,
                                          face_tracking.eye_blink_rate)
                            .Build();

    // Then
    EXPECT_EQ(result.face_tracking, face_tracking);
}
}  // namespace
}  // namespace support
}  // namespace test
}  // namespace driver
}  // namespace perception
