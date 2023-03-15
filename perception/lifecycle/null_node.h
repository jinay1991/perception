///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_LIFECYCLE_NODE_NULL_NODE_H
#define PERCEPTION_LIFECYCLE_NODE_NULL_NODE_H

#include "perception/lifecycle/i_node.h"

namespace perception
{
namespace lifecycle
{

/// @brief Interface to the null node
class NullNode : public INode
{
  public:
    /// @brief Perform Initialization of the Node
    void Init() override {}

    /// @brief Perform Cyclic Step of the Node
    void Step() override {}

    /// @brief Perform Shutdown of the Node
    void Shutdown() override {}

    /// @brief Provide Node Name
    ///
    /// @return name of the node
    std::string GetName() const { return "null_node"; }
};

}  // namespace lifecycle
}  // namespace perception
#endif  /// PERCEPTION_LIFECYCLE_NODE_NULL_NODE_H
