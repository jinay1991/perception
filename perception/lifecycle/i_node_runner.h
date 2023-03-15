///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_LIFECYCLE_NODE_I_NODE_RUNNER_H
#define PERCEPTION_LIFECYCLE_NODE_I_NODE_RUNNER_H

#include "perception/lifecycle/i_node.h"

#include <chrono>
#include <string>

namespace perception
{
namespace lifecycle
{

/// @brief Interface to the middleware node runner
class INodeRunner
{
  public:
    /// @brief Default Destructor
    virtual ~INodeRunner() = default;

    /// @brief Register a Node
    ///
    /// @param node [in] - instance of the node to be run
    virtual void RegisterNode(NodePtr node) = 0;

    /// @brief Run node once
    virtual void RunOnce() = 0;

    /// @brief Run node for provided duration and it's step size.
    ///
    /// @param duration [in] - Duration for which node will continue to run
    /// @param step [in] - Duration interval for which node will be stepped.
    virtual void RunForDuration(const std::chrono::milliseconds duration, const std::chrono::milliseconds step) = 0;
};

}  // namespace lifecycle
}  // namespace perception
#endif  /// PERCEPTION_LIFECYCLE_NODE_I_NODE_RUNNER_H
