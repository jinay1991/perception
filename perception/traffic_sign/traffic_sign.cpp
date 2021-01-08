///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/traffic_sign/traffic_sign.h"

namespace perception
{
TrafficSign::TrafficSign()
    : inference_engine_params_{}, inference_engine_{}, camera_message_{}, traffic_sign_list_message_{}
{
}

void TrafficSign::Init()
{
    inference_engine_.SelectInferenceEngine(InferenceEngineType::kTensorFlow, inference_engine_params_);
    inference_engine_.Init();
}

void TrafficSign::Step()
{
    inference_engine_.Execute(camera_message_.undistorted_image);

    UpdateOutputs();
}

void TrafficSign::Shutdown() {}

void TrafficSign::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

const TrafficSignListMessage& TrafficSign::GetTrafficSignListMessage() const
{
    return traffic_sign_list_message_;
}

void TrafficSign::UpdateOutputs()
{
    // extract outputs
}

}  // namespace perception
