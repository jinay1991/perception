///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H
#define PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H

#include "middleware/communication/i_pub_sub_factory.h"
#include "middleware/lifecycle/node.h"
#include "perception/sensor/camera/camera.h"

#include <memory>
#include <string>

namespace perception
{

class CameraNode : public middleware::Node
{
  public:
    explicit CameraNode(middleware::IPubSubFactory& factory);

    ~CameraNode() = default;

    void Init() override;
    void ExecuteStep() override;
    void Shutdown() override;

    void SetSource(const std::string& source);

  private:
    virtual void InitPublisher();

    std::string source_;
    std::unique_ptr<Camera> camera_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_NODE_H
