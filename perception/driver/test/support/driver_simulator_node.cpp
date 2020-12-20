///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/test/support/driver_simulator_node.h"

#include "perception/communication/topics.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

namespace perception
{

DriverSimulatorNode::DriverSimulatorNode(middleware::IPubSubFactory& factory)
    : middleware::Node{"driver_simulator_node", factory},
      driver_camera_message_{DriverCameraMessageBuilder()
                                 .WithHeadPose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithGazePose(0.0_rad, 0.0_rad, 0.0_rad)
                                 .WithEyeState(true, true)
                                 .Build()}
{
}

void DriverSimulatorNode::Init()
{
    AddPublisher<DriverCameraTopic>(
        [&driver_camera_message = driver_camera_message_] { return driver_camera_message; });
}

void DriverSimulatorNode::ExecuteStep() {}

void DriverSimulatorNode::Shutdown() {}

void DriverSimulatorNode::OpenEyes()
{
    driver_camera_message_.face_tracking.eye_lid_opening = kMaxEyeLidOpening;
    driver_camera_message_.face_tracking.eye_visibility = true;
    driver_camera_message_.face_tracking.face_visibility = true;
}

void DriverSimulatorNode::CloseEyes()
{
    driver_camera_message_.face_tracking.eye_lid_opening = 0.0_mm;
    driver_camera_message_.face_tracking.eye_visibility = true;
    driver_camera_message_.face_tracking.face_visibility = true;
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
