///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CAMERA_SYSTEM_BUILDER_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CAMERA_SYSTEM_BUILDER_H

#include "perception/datatypes/driver.h"

#include <units.h>

namespace perception
{
using namespace units::literals;

class DriverCameraSystemBuilder
{
  public:
    DriverCameraSystemBuilder();

    DriverCameraSystemBuilder& WithFaceTracking(const FaceTracking& face_tracking);
    DriverCameraSystemBuilder& WithHeadTracking(const HeadTracking& head_tracking);
    DriverCameraSystemBuilder& WithGazeTracking(const GazeTracking& gaze_tracking);

    DriverCameraSystemBuilder& WithHeadPose(const units::angle::radian_t yaw,
                                            const units::angle::radian_t pitch,
                                            const units::angle::radian_t roll);
    DriverCameraSystemBuilder& WithGazePose(const units::angle::radian_t yaw,
                                            const units::angle::radian_t pitch,
                                            const units::angle::radian_t roll);
    DriverCameraSystemBuilder& WithEyeState(const bool eyes_visible,
                                            const units::length::millimeter_t eye_lid_opening = 1.0_mm,
                                            const units::frequency::hertz_t eye_blink_rate = 1.0_Hz);

    DriverCameraSystem Build() const;

  private:
    DriverCameraSystem driver_camera_system_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_CAMERA_SYSTEM_BUILDER_H
