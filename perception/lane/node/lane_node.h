///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_LANE_NODE_LANE_NODE_H
#define PERCEPTION_LANE_NODE_LANE_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/datatypes/camera.h"
#include "perception/datatypes/lane.h"

namespace perception
{
class LaneNode : public middleware::Node
{
  public:
    explicit LaneNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

  private:
    LaneMessage lane_message_;
    CameraMessage camera_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_LANE_NODE_LANE_NODE_H
