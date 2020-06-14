///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_LANE_LANE_DETECT_H
#define PERCEPTION_LANE_LANE_DETECT_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"

namespace perception
{
class LaneDetect : public middleware::Node
{
  public:
    explicit LaneDetect(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;
};
}  // namespace perception

#endif  /// PERCEPTION_LANE_LANE_DETECT_H
