///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/node/driver_node.h"

#include "middleware/lifecycle/node.h"

namespace perception
{
DriverNode::DriverNode(middleware::IPubSubFactory& factory) : middleware::Node{"driver_node", factory}, driver_{} {}
void DriverNode::Init() {}
void DriverNode::ExecuteStep() {}
void DriverNode::Shutdown() {}

}  // namespace perception
