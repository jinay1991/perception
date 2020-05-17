///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/lane/lane_detect.h"

namespace perception
{
LaneDetect::LaneDetect() : camera_{} {}

void LaneDetect::Init()
{
    camera_.Init();
}
void LaneDetect::Execute()
{
    camera_.Execute();
}
void LaneDetect::Shutdown()
{
    camera_.Shutdown();
}
}  // namespace perception
