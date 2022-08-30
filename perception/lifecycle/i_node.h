///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#ifndef PERCEPTION_LIFECYCLE_NODE_I_NODE_H
#define PERCEPTION_LIFECYCLE_NODE_I_NODE_H

#include <memory>
#include <string>

namespace perception
{
namespace lifecycle
{

/// @brief Interface to the middleware node
class INode
{
  public:
    /// @brief Default Destructor
    virtual ~INode() = default;

    /// @brief Perform Initialization of the Node
    virtual void Init() = 0;

    /// @brief Perform Cyclic Step of the Node
    virtual void Step() = 0;

    /// @brief Perform Shutdown of the Node
    virtual void Shutdown() = 0;

    /// @brief Provide Node name
    ///
    /// @return name of the node
    virtual std::string GetName() const = 0;
};

/// @brief Pointer definition of INode
using NodePtr = std::unique_ptr<INode>;

}  // namespace lifecycle
}  // namespace perception
#endif  /// PERCEPTION_LIFECYCLE_NODE_I_NODE_H
