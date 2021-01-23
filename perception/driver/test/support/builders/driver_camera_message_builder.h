///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_BUILDER_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_BUILDER_H

#include "perception/datatypes/driver.h"

#include <units.h>

#include <chrono>

namespace perception
{

class DriverCameraMessageBuilder
{
  public:
    DriverCameraMessageBuilder();

    DriverCameraMessageBuilder& WithTimePoint(const std::chrono::system_clock::time_point& time_point);
    DriverCameraMessageBuilder& WithFaceTracking(const FaceTracking& face_tracking);
    DriverCameraMessageBuilder& WithHeadTracking(const HeadTracking& head_tracking);
    DriverCameraMessageBuilder& WithGazeTracking(const GazeTracking& gaze_tracking);

    DriverCameraMessageBuilder& WithHeadPose(const units::angle::radian_t yaw,
                                             const units::angle::radian_t pitch,
                                             const units::angle::radian_t roll);
    DriverCameraMessageBuilder& WithGazePose(const units::angle::radian_t yaw,
                                             const units::angle::radian_t pitch,
                                             const units::angle::radian_t roll);

    DriverCameraMessageBuilder& WithEyeState(const bool face_visible,
                                             const bool eye_visible,
                                             const units::length::millimeter_t eye_lid_opening = 1.0_mm,
                                             const units::frequency::hertz_t eye_blink_rate = 1.0_Hz);

    const DriverCameraMessage& Build() const;

  private:
    DriverCameraMessage driver_camera_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_BUILDERS_DRIVER_CAMERA_BUILDER_H
