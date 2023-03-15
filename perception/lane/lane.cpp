///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/lane/lane.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

namespace perception
{
Lane::Lane() : camera_message_{}, lane_message_{} {}

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
