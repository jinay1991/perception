///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
class DriverSimulator
{
  public:
    DriverSimulator();

    void Step();

    const DriverCameraMessage& GetDriverCameraMessage() const;

    void ShowFace();
    void HideFace();

    void OpenEyes();
    void CloseEyes();
    void BlinkEyes(const units::frequency::hertz_t eye_blink_rate);

    void LookStraight();
    void LookDown();
    void LookUp();
    void LookLeft();
    void LookRight();

    void MoveHeadUp(const units::angle::radian_t delta_pitch);
    void MoveHeadDown(const units::angle::radian_t delta_pitch);
    void MoveHeadLeft(const units::angle::radian_t delta_yaw);
    void MoveHeadRight(const units::angle::radian_t delta_yaw);

    void TiltHeadLeft(const units::angle::radian_t delta_roll);
    void TiltHeadRight(const units::angle::radian_t delta_roll);

    void MoveGazeUp(const units::angle::radian_t delta_pitch);
    void MoveGazeDown(const units::angle::radian_t delta_pitch);
    void MoveGazeLeft(const units::angle::radian_t delta_yaw);
    void MoveGazeRight(const units::angle::radian_t delta_yaw);

  private:
    void ToggleEyes();

    std::chrono::milliseconds GetEyeBlinkDuration() const;

    std::chrono::milliseconds time_since_last_eye_state_change_;
    DriverCameraMessage driver_camera_message_;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_H
