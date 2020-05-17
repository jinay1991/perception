///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/middleware/lifecycle/node.h"

namespace perception
{
Node::Node(const std::string name, IPubSubFactory& factory) : name_{name}, factory_{&factory} {}
std::string Node::GetName() const
{
    return name_;
}

}  // namespace perception
