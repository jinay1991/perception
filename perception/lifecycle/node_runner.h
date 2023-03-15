///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_LIFECYCLE_NODE_RUNNER_H
#define PERCEPTION_LIFECYCLE_NODE_RUNNER_H

#include "perception/lifecycle/i_node_runner.h"

#include <map>

namespace perception
{
namespace lifecycle
{

/// @brief Default Cycle Duration
static constexpr std::chrono::milliseconds kDefaultCycleDuration{40UL};

/// @brief Node Runner (middleware)
class NodeRunner : public INodeRunner
{
  public:
    /// @brief Default Constructor
    NodeRunner();

    /// @brief Register a Node
    ///
    /// @param node [in] - instance of the node to be run
    void RegisterNode(NodePtr node) override;

    /// @brief Run node once
    void RunOnce() override;

    /// @brief Run node for provided duration and it's step size.
    ///
    /// @param duration [in] - Duration for which node will continue to run
    /// @param step [in] - Duration interval for which node will be stepped.
    void RunForDuration(const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kDefaultCycleDuration) override;

    /// @brief Provide whether node is registered with the name provided
    ///
    /// @return True if node is registered with same name, otherwise False.
    bool IsNodeRegistered(const std::string name) const;

  private:
    /// @brief list of registered node
    std::map<std::string, NodePtr> node_map_;
};

}  // namespace lifecycle
}  // namespace perception
#endif  /// PERCEPTION_LIFECYCLE_NODE_RUNNER_H
