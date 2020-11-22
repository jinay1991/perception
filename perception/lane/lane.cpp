///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/lane/lane.h"

namespace perception
{
Lane::Lane() : lane_message_{}, camera_message_{} {}

void Lane::Init() {}

void Lane::Step() {}

void Lane::Shutdown() {}

void Lane::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

const LaneMessage& Lane::GetLaneMessage() const
{
    return lane_message_;
}

void Lane::UpdateOutputs()
{
    // update output
}

}  // namespace perception
