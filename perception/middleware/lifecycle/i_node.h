///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_LIFECYCLE_I_NODE_H_
#define PERCEPTION_MIDDLEWARE_LIFECYCLE_I_NODE_H_

#include <string>

namespace perception
{

class INode
{
  public:
    virtual ~INode() = default;

    virtual void Init() = 0;
    virtual void Execute() = 0;
    virtual void Shutdown() = 0;

    virtual std::string GetName() const = 0;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_LIFECYCLE_I_NODE_H_
