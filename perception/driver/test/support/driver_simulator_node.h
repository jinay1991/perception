///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_NODE_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_NODE_H

#include "middleware/lifecycle/node.h"
#include "perception/datatypes/driver.h"

namespace perception
{
class DriverSimulatorNode : public middleware::Node
{
  public:
    explicit DriverSimulatorNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

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

    void MoveHeadUp(const units::angle::radian_t delta_roll);
    void MoveHeadDown(const units::angle::radian_t delta_roll);
    void MoveHeadLeft(const units::angle::radian_t delta_yaw);
    void MoveHeadRight(const units::angle::radian_t delta_yaw);

    void TiltHeadLeft(const units::angle::radian_t delta_pitch);
    void TiltHeadRight(const units::angle::radian_t delta_pitch);

  private:
    void ToggleEyes();

    std::chrono::milliseconds GetEyeBlinkDuration() const;

    std::chrono::milliseconds time_since_last_eye_state_change_;
    DriverCameraMessage driver_camera_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_TEST_SUPPORT_DRIVER_SIMULATOR_NODE_H
