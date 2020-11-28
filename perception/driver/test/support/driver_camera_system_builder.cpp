///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/driver_camera_system_builder.h"

namespace perception
{
DriverCameraSystemBuilder::DriverCameraSystemBuilder() : driver_camera_system_{} {}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithFaceTracking(const FaceTracking& face_tracking)
{
    driver_camera_system_.face_tracking = face_tracking;
    return *this;
}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithHeadTracking(const HeadTracking& head_tracking)
{
    driver_camera_system_.head_tracking = head_tracking;
    return *this;
}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithGazeTracking(const GazeTracking& gaze_tracking)
{
    driver_camera_system_.gaze_tracking = gaze_tracking;
    return *this;
}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithHeadPose(const units::angle::radian_t yaw,
                                                                   const units::angle::radian_t pitch,
                                                                   const units::angle::radian_t roll)
{
    const HeadTracking head_tracking{yaw, pitch, roll};
    return WithHeadTracking(head_tracking);
}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithGazePose(const units::angle::radian_t yaw,
                                                                   const units::angle::radian_t pitch,
                                                                   const units::angle::radian_t roll)
{
    const GazeTracking gaze_tracking{yaw, pitch, roll};
    return WithGazeTracking(gaze_tracking);
}

DriverCameraSystemBuilder& DriverCameraSystemBuilder::WithEyeState(const bool eye_visibility,
                                                                   const units::length::millimeter_t eye_lid_opening,
                                                                   const units::frequency::hertz_t eye_blink_rate)
{
    const FaceTracking face_tracking{eye_visibility, eye_lid_opening, eye_blink_rate};
    return WithFaceTracking(face_tracking);
}

DriverCameraSystem DriverCameraSystemBuilder::Build() const
{
    return driver_camera_system_;
}
}  // namespace perception
