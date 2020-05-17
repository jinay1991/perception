///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_LANE_LANE_DETECT_H_
#define PERCEPTION_LANE_LANE_DETECT_H_

#include "perception/sensor/camera/camera.h"

namespace perception
{
class LaneDetect
{
  public:
    LaneDetect();

    virtual void Init();
    virtual void Execute();
    virtual void Shutdown();

  private:
    Camera camera_;
};
}  // namespace perception

#endif  /// PERCEPTION_LANE_LANE_DETECT_H_
