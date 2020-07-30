///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

#include <opencv4/opencv2/core.hpp>

namespace perception
{
Object::Object()
    : inference_engine_params_{"external/ssd_mobilenet_v2_coco/saved_model",
                               "image_tensor",
                               {"detection_classes", "detection_scores", "detection_boxes"}},
      inference_engine_{},
      camera_message_{},
      object_list_message_{}
{
}

void Object::Init()
{
    inference_engine_.SelectInferenceEngine(InferenceEngineType::kTensorFlow, inference_engine_params_);
    inference_engine_.Init();
}

void Object::Step()
{
    inference_engine_.Execute(camera_message_.undistorted_image);

    UpdateOutputs();
}

void Object::Shutdown()
{
    inference_engine_.Shutdown();
}

void Object::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

ObjectListMessage Object::GetObjectListMessage() const
{
    return object_list_message_;
}

void Object::UpdateOutputs()
{
    const auto results = inference_engine_.GetResults();
    const cv::Mat detection_classes = results.at(0);
    const cv::Mat detection_scores = results.at(1);
    const cv::Mat detection_boxes = results.at(2);
}
}  // namespace perception
