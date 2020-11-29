///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/builders/driver_camera_system_message_builder.h"

namespace perception
{
DriverCameraSystemMessageBuilder::DriverCameraSystemMessageBuilder() : driver_camera_system_message_{} {}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithTimePoint(
    const std::chrono::system_clock::time_point& time_point)
{
    driver_camera_system_message_.time_point = time_point;
    return *this;
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithFaceTracking(const FaceTracking& face_tracking)
{
    driver_camera_system_message_.face_tracking = face_tracking;
    return *this;
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithHeadTracking(const HeadTracking& head_tracking)
{
    driver_camera_system_message_.head_tracking = head_tracking;
    return *this;
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithGazeTracking(const GazeTracking& gaze_tracking)
{
    driver_camera_system_message_.gaze_tracking = gaze_tracking;
    return *this;
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithHeadPose(const units::angle::radian_t yaw,
                                                                                 const units::angle::radian_t pitch,
                                                                                 const units::angle::radian_t roll)
{
    const HeadTracking head_tracking{yaw, pitch, roll};
    return WithHeadTracking(head_tracking);
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithGazePose(const units::angle::radian_t yaw,
                                                                                 const units::angle::radian_t pitch,
                                                                                 const units::angle::radian_t roll)
{
    const GazeTracking gaze_tracking{yaw, pitch, roll};
    return WithGazeTracking(gaze_tracking);
}

DriverCameraSystemMessageBuilder& DriverCameraSystemMessageBuilder::WithEyeState(
    const bool eye_visibility,
    const units::length::millimeter_t eye_lid_opening,
    const units::frequency::hertz_t eye_blink_rate)
{
    const FaceTracking face_tracking{eye_visibility, eye_lid_opening, eye_blink_rate};
    return WithFaceTracking(face_tracking);
}

DriverCameraSystemMessage DriverCameraSystemMessageBuilder::Build() const
{
    return driver_camera_system_message_;
}
}  // namespace perception
