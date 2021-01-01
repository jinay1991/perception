///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_TRAFFIC_SIGN_NODE_TRAFFIC_SIGN_NODE_H
#define PERCEPTION_TRAFFIC_SIGN_NODE_TRAFFIC_SIGN_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/datatypes/camera.h"
#include "perception/datatypes/traffic_sign.h"
#include "perception/traffic_sign/traffic_sign.h"

namespace perception
{
class TrafficSignNode : public middleware::Node
{
  public:
    explicit TrafficSignNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

  private:
    TrafficSign traffic_sign_;
};
}  // namespace perception

#endif  /// PERCEPTION_TRAFFIC_SIGN_NODE_TRAFFIC_SIGN_NODE_H
