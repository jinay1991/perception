///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_LIFECYCLE_NODE_NODE_H
#define PERCEPTION_LIFECYCLE_NODE_NODE_H

#include "perception/lifecycle/i_node.h"

namespace perception
{
namespace lifecycle
{

/// @brief Interface to the middleware node
class Node : public INode
{
  public:
    /// @brief Default Constructor
    ///
    /// @param name [in] - Name of the Node
    explicit Node(const std::string name);

    /// @brief Provide Node name
    ///
    /// @return name
    std::string GetName() const override;

  private:
    /// @brief Name of the Node
    std::string name_;
};

}  // namespace lifecycle
}  // namespace perception
#endif  /// PERCEPTION_LIFECYCLE_NODE_NODE_H
