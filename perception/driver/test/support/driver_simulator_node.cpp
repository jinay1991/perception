///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/driver_simulator_node.h"

#include "perception/communication/topics.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

namespace perception
{
using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kSystemCycleDuration{40U};

DriverSimulatorNode::DriverSimulatorNode(middleware::IPubSubFactory& factory)
    : middleware::Node{"driver_simulator_node", factory},
      time_since_last_eye_state_change_{0U},
      driver_camera_message_{DriverCameraMessageBuilder()
                                 .WithHeadPose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithGazePose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithEyeState(true, true, kMaxEyeLidOpening, kMaxEyeBlinkRate)
                                 .Build()}
{
}

void DriverSimulatorNode::Init()
{
    AddPublisher<DriverCameraTopic>(
        [&driver_camera_message = driver_camera_message_] { return driver_camera_message; });
}

void DriverSimulatorNode::ExecuteStep()
{
    ToggleEyes();
}

void DriverSimulatorNode::Shutdown() {}

void DriverSimulatorNode::ToggleEyes()
{
    if (time_since_last_eye_state_change_ > GetEyeBlinkDuration())
    {
        const bool is_eye_open = driver_camera_message_.face_tracking.eye_lid_opening == kMaxEyeLidOpening;
        if (is_eye_open)
        {
            CloseEyes();
            time_since_last_eye_state_change_ = 0ms;
        }
        else
        {
            OpenEyes();
            time_since_last_eye_state_change_ = 0ms;
        }
    }
    time_since_last_eye_state_change_ += kSystemCycleDuration;
}

std::chrono::milliseconds DriverSimulatorNode::GetEyeBlinkDuration() const
{
    const double eye_blink_rate = driver_camera_message_.face_tracking.eye_blink_rate.value();
    std::chrono::milliseconds eye_blink_duration{0U};
    if (eye_blink_rate != 0.0)
    {
        eye_blink_duration = std::chrono::seconds{static_cast<std::uint32_t>(std::floor(1.0 / eye_blink_rate))};
    }
    return eye_blink_duration;
}

void DriverSimulatorNode::ShowFace()
{
    driver_camera_message_.face_tracking.face_visibility = true;
    driver_camera_message_.face_tracking.eye_visibility = true;
}

void DriverSimulatorNode::HideFace()
{
    driver_camera_message_.face_tracking.face_visibility = false;
    driver_camera_message_.face_tracking.eye_visibility = false;
}

void DriverSimulatorNode::OpenEyes()
{
    ShowFace();
    driver_camera_message_.face_tracking.eye_lid_opening = kMaxEyeLidOpening;
}

void DriverSimulatorNode::CloseEyes()
{
    ShowFace();
    driver_camera_message_.face_tracking.eye_lid_opening = 0.0_mm;
}

void DriverSimulatorNode::BlinkEyes(const units::frequency::hertz_t eye_blink_rate)
{
    driver_camera_message_.face_tracking.eye_blink_rate = eye_blink_rate;
}

void DriverSimulatorNode::LookStraight()
{
    driver_camera_message_.head_tracking.roll = 0.0_deg;
}

void DriverSimulatorNode::LookDown()
{
    MoveHeadDown(kMaxHeadPoseRoll);
}

void DriverSimulatorNode::LookUp()
{
    MoveHeadUp(kMaxHeadPoseRoll);
}

void DriverSimulatorNode::LookLeft()
{
    MoveHeadLeft(kMaxHeadPoseYaw);
}

void DriverSimulatorNode::LookRight()
{
    MoveHeadRight(kMaxHeadPoseYaw);
}

void DriverSimulatorNode::MoveHeadUp(const units::angle::radian_t delta_roll)
{
    driver_camera_message_.head_tracking.roll += delta_roll;
}

void DriverSimulatorNode::MoveHeadDown(const units::angle::radian_t delta_roll)
{
    driver_camera_message_.head_tracking.roll -= delta_roll;
}

void DriverSimulatorNode::MoveHeadLeft(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.head_tracking.yaw += delta_yaw;
}

void DriverSimulatorNode::MoveHeadRight(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.head_tracking.yaw -= delta_yaw;
}

void DriverSimulatorNode::TiltHeadLeft(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.head_tracking.pitch += delta_pitch;
}

void DriverSimulatorNode::TiltHeadRight(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.head_tracking.pitch -= delta_pitch;
}
}  // namespace perception
