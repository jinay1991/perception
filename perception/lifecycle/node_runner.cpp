///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#include "perception/lifecycle/node_runner.h"

#include <functional>
#include <iostream>

namespace perception
{
namespace lifecycle
{

NodeRunner::NodeRunner() : node_map_{} {}

void NodeRunner::RegisterNode(NodePtr node)
{
    node_map_.emplace(node->GetName(), std::move(node));
}

void NodeRunner::RunOnce()
{
    for (auto& node : node_map_)
    {
        node.second.get()->Init();
        node.second.get()->Step();
        node.second.get()->Shutdown();
    }
}

void NodeRunner::RunForDuration(const std::chrono::milliseconds duration, const std::chrono::milliseconds step)
{
    using namespace std::chrono_literals;

    for (auto& node : node_map_)
    {
        node.second.get()->Init();
        for (auto time_passed = 0ms; time_passed < duration; time_passed += step)
        {
            node.second.get()->Step();
            std::cout << "Time passed: " << time_passed.count() << "ms, Duration: " << duration.count()
                      << " ms, with step: " << step.count() << "ms." << std::endl;
        }
        node.second.get()->Shutdown();
    }
}

bool NodeRunner::IsNodeRegistered(const std::string name) const
{
    return (node_map_.find(name) != node_map_.end());
}

}  // namespace lifecycle
}  // namespace perception
