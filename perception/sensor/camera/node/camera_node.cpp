///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/node/camera_node.h"

#include "perception/communication/topics.h"

namespace perception
{
CameraNode::CameraNode(middleware::IPubSubFactory& factory)
    : Node{"camera_node", factory}, source_{"data/grace_hopper.jpg"}, camera_{source_}
{
}

void CameraNode::Init()
{
    camera_.Init();
    InitPublisher();
}

void CameraNode::InitPublisher()
{
    AddPublisher<CameraTopic>([this]() { return camera_.GetCameraMessage(); });
}

void CameraNode::ExecuteStep()
{
    camera_.Step();
}

void CameraNode::Shutdown()
{
    camera_.Shutdown();
}

void CameraNode::SetSource(const std::string& source)
{
    source_ = source;
    camera_.SetSource(source_);
}

}  // namespace perception
