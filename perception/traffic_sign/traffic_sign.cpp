///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/traffic_sign/traffic_sign.h"

namespace perception
{
TrafficSign::TrafficSign() : camera_message_{}, traffic_sign_list_message_{} {}

void TrafficSign::Init() {}

void TrafficSign::Step() {}

void TrafficSign::Shutdown() {}

void TrafficSign::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

const TrafficSignListMessage& TrafficSign::GetTrafficSignListMessage() const
{
    return traffic_sign_list_message_;
}

void TrafficSign::UpdateOutputs()
{
    // update output
}
}  // namespace perception
