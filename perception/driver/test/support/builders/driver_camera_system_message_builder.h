///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_SYSTEM_BUILDER_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_SYSTEM_BUILDER_H

#include "perception/datatypes/driver.h"

#include <units.h>

#include <chrono>

namespace perception
{

class DriverCameraSystemMessageBuilder
{
  public:
    DriverCameraSystemMessageBuilder();

    DriverCameraSystemMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);
    DriverCameraSystemMessageBuilder& WithFaceTracking(const FaceTracking& face_tracking);
    DriverCameraSystemMessageBuilder& WithHeadTracking(const HeadTracking& head_tracking);
    DriverCameraSystemMessageBuilder& WithGazeTracking(const GazeTracking& gaze_tracking);

    DriverCameraSystemMessageBuilder& WithHeadPose(const units::angle::radian_t yaw,
                                                   const units::angle::radian_t pitch,
                                                   const units::angle::radian_t roll);
    DriverCameraSystemMessageBuilder& WithGazePose(const units::angle::radian_t yaw,
                                                   const units::angle::radian_t pitch,
                                                   const units::angle::radian_t roll);
    DriverCameraSystemMessageBuilder& WithEyeState(const bool eyes_visible,
                                                   const units::length::millimeter_t eye_lid_opening = 1.0_mm,
                                                   const units::frequency::hertz_t eye_blink_rate = 1.0_Hz);

    DriverCameraSystemMessage Build() const;

  private:
    DriverCameraSystemMessage driver_camera_system_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_SYSTEM_BUILDER_H
