///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_OBJECT_OBJECT_NODE_H
#define PERCEPTION_OBJECT_OBJECT_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/datatypes/camera.h"
#include "perception/datatypes/object.h"

namespace perception
{
class ObjectNode : public middleware::Node
{
  public:
    explicit ObjectNode(middleware::IPubSubFactory& factory);

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

  private:
    ObjectMessage object_message_;
    CameraMessage camera_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_OBJECT_NODE_H