///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

namespace perception
{
namespace driver
{
namespace test
{
namespace support
{
DriverCameraMessageBuilder::DriverCameraMessageBuilder() : driver_camera_message_{} {}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithTimePoint(
    const std::chrono::system_clock::time_point& time_point)
{
    driver_camera_message_.time_point = time_point;
    return *this;
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithFaceTracking(const FaceTracking& face_tracking)
{
    driver_camera_message_.face_tracking = face_tracking;
    return *this;
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithHeadTracking(const HeadTracking& head_tracking)
{
    driver_camera_message_.head_tracking = head_tracking;
    return *this;
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithGazeTracking(const GazeTracking& gaze_tracking)
{
    driver_camera_message_.gaze_tracking = gaze_tracking;
    return *this;
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithHeadPose(const units::angle::radian_t yaw,
                                                                     const units::angle::radian_t pitch,
                                                                     const units::angle::radian_t roll)
{
    const HeadTracking head_tracking{yaw, pitch, roll};
    return WithHeadTracking(head_tracking);
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithGazePose(const units::angle::radian_t yaw,
                                                                     const units::angle::radian_t pitch,
                                                                     const units::angle::radian_t roll)
{
    const GazeTracking gaze_tracking{yaw, pitch, roll};
    return WithGazeTracking(gaze_tracking);
}

DriverCameraMessageBuilder& DriverCameraMessageBuilder::WithEyeState(const bool face_visible,
                                                                     const bool eye_visible,
                                                                     const units::length::millimeter_t eye_lid_opening,
                                                                     const units::frequency::hertz_t eye_blink_rate)
{
    const FaceTracking face_tracking{face_visible, eye_visible, eye_lid_opening, eye_blink_rate};
    return WithFaceTracking(face_tracking);
}

const DriverCameraMessage& DriverCameraMessageBuilder::Build() const
{
    return driver_camera_message_;
}
}  // namespace support
}  // namespace test
}  // namespace driver
}  // namespace perception
