///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/lifecycle/node.h"

namespace perception
{
namespace lifecycle
{

Node::Node(const std::string name) : name_{name} {}

std::string Node::GetName() const
{
    return name_;
}

}  // namespace lifecycle
}  // namespace perception
