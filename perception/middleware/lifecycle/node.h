///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_LIFECYCLE_NODE_H_
#define PERCEPTION_MIDDLEWARE_LIFECYCLE_NODE_H_

#include "perception/middleware/communication/i_pub_sub_factory.h"
#include "perception/middleware/lifecycle/i_node.h"

#include <string>

namespace perception
{

class Node : public INode
{
  public:
    explicit Node(const std::string name, IPubSubFactory& factory);
    ~Node() = default;

    std::string GetName() const override;

  private:
    const std::string name_;
    IPubSubFactory* factory_;
};
}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_LIFECYCLE_NODE_H_
