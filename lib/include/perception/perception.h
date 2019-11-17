///
/// @file
///
#ifndef PERCEPTION_PERCEPTION_H_
#define PERCEPTION_PERCEPTION_H_

#include <memory>

#include "perception/lane_detect/i_lane_detect.h"
#include "perception/object_detect/i_object_detect.h"
#include "perception/traffic_light_detect/i_traffic_light_detect.h"
#include "perception/traffic_sign_detect/i_traffic_sign_detect.h"

namespace perception
{
class Perception
{
  public:
    Perception();

  private:
    std::unique_ptr<ILaneDetect> lane_detect_;
    std::unique_ptr<IObjectDetect> object_detect_;
    std::unique_ptr<ITrafficLightDetect> traffic_light_detect_;
    std::unique_ptr<ITrafficSignDetect> traffic_sign_detect_;
};
}  // namespace perception

#endif  /// PERCEPTION_TRAFFIC_SIGN_DETECT_I_TRAFFIC_SIGN_DETECT_H_