///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/lane/lane_detect.h"

namespace perception
{
LaneDetect::LaneDetect(middleware::IPubSubFactory& factory) : Node{"lane_detection_node", factory} {}

void LaneDetect::Init() {}
void LaneDetect::ExecuteStep() {}
void LaneDetect::Shutdown() {}
}  // namespace perception
