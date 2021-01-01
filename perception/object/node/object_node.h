///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_OBJECT_NODE_OBJECT_NODE_H
#define PERCEPTION_OBJECT_NODE_OBJECT_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/object/object.h"

namespace perception
{
/// @brief Object Detection Node
class ObjectNode final : public middleware::Node
{
  public:
    /// @brief Constructor
    /// @param factory [in] Middleware Publisher/Subscriber Factory
    explicit ObjectNode(middleware::IPubSubFactory& factory);

    /// @brief Initialize Object Detection
    void Init() override;

    /// @brief Execute single step for Object Detection
    void ExecuteStep() override;

    /// @brief Shutdown/Deinitialize Object Detection
    void Shutdown() override;

  private:
    /// @brief Instance of Object Detection algorithm
    Object object_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_NODE_OBJECT_NODE_H
