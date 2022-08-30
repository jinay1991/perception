///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/test/support/driver_simulator.h"

#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

namespace perception
{
namespace driver
{
namespace
{
constexpr bool IsEyeOpen(const units::length::millimeter_t eye_lid_opening) noexcept
{
    /// @TODO: Is checking with MaxEyeLidOpening good enough to determine eye state to be OPEN?
    return (eye_lid_opening == kMaxEyeLidOpening);
}
}  // namespace
using namespace units::literals;

DriverSimulator::DriverSimulator()
    : time_since_last_eye_state_change_{0U},
      driver_camera_message_{test::support::DriverCameraMessageBuilder()
                                 .WithHeadPose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithGazePose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithEyeState(true, true, kMaxEyeLidOpening, kMaxEyeBlinkRate)
                                 .Build()}
{
}

void DriverSimulator::Step()
{
    ToggleEyes();
}

const DriverCameraMessage& DriverSimulator::GetDriverCameraMessage() const
{
    return driver_camera_message_;
}

void DriverSimulator::ToggleEyes()
{
    if (time_since_last_eye_state_change_ > GetEyeBlinkDuration())
    {
        if (IsEyeOpen(driver_camera_message_.face_tracking.eye_lid_opening))
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
    time_since_last_eye_state_change_ += kMaxCycleDuration;
}

std::chrono::milliseconds DriverSimulator::GetEyeBlinkDuration() const
{
    const double eye_blink_rate = driver_camera_message_.face_tracking.eye_blink_rate.value();
    std::chrono::milliseconds eye_blink_duration{0UL};
    if (eye_blink_rate != 0.0)
    {
        eye_blink_duration = std::chrono::seconds{static_cast<std::uint32_t>(std::floor(1.0 / eye_blink_rate))};
    }
    return eye_blink_duration;
}

void DriverSimulator::ShowFace()
{
    driver_camera_message_.face_tracking.face_visible = true;
    driver_camera_message_.face_tracking.eye_visible = true;
}

void DriverSimulator::HideFace()
{
    driver_camera_message_.face_tracking.face_visible = false;
    driver_camera_message_.face_tracking.eye_visible = false;
}

void DriverSimulator::OpenEyes()
{
    ShowFace();
    driver_camera_message_.face_tracking.eye_lid_opening = kMaxEyeLidOpening;
}

void DriverSimulator::CloseEyes()
{
    ShowFace();
    driver_camera_message_.face_tracking.eye_lid_opening = kMinEyeLidOpening;
}

void DriverSimulator::BlinkEyes(const units::frequency::hertz_t eye_blink_rate)
{
    driver_camera_message_.face_tracking.eye_blink_rate = eye_blink_rate;
}

void DriverSimulator::LookStraight()
{
    driver_camera_message_.head_tracking.roll = 0.0_deg;
    driver_camera_message_.head_tracking.pitch = 0.0_deg;
    driver_camera_message_.head_tracking.yaw = 0.0_deg;
}

void DriverSimulator::LookDown()
{
    MoveHeadDown(kMinHeadPosePitch);
}

void DriverSimulator::LookUp()
{
    MoveHeadUp(kMaxHeadPosePitch);
}

void DriverSimulator::LookLeft()
{
    MoveHeadLeft(kMinHeadPoseYaw);
}

void DriverSimulator::LookRight()
{
    MoveHeadRight(kMaxHeadPoseYaw);
}

void DriverSimulator::MoveHeadUp(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.head_tracking.pitch += delta_pitch;
}

void DriverSimulator::MoveHeadDown(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.head_tracking.pitch -= delta_pitch;
}

void DriverSimulator::MoveHeadLeft(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.head_tracking.yaw -= delta_yaw;
}

void DriverSimulator::MoveHeadRight(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.head_tracking.yaw += delta_yaw;
}

void DriverSimulator::TiltHeadLeft(const units::angle::radian_t delta_roll)
{
    driver_camera_message_.head_tracking.roll -= delta_roll;
}

void DriverSimulator::TiltHeadRight(const units::angle::radian_t delta_roll)
{
    driver_camera_message_.head_tracking.roll += delta_roll;
}

void DriverSimulator::MoveGazeUp(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.gaze_tracking.pitch += delta_pitch;
}

void DriverSimulator::MoveGazeDown(const units::angle::radian_t delta_pitch)
{
    driver_camera_message_.gaze_tracking.pitch -= delta_pitch;
}

void DriverSimulator::MoveGazeLeft(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.gaze_tracking.yaw -= delta_yaw;
}

void DriverSimulator::MoveGazeRight(const units::angle::radian_t delta_yaw)
{
    driver_camera_message_.gaze_tracking.yaw += delta_yaw;
}
}  // namespace driver
}  // namespace perception
