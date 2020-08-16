///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/opencv_inference_engine.h"

#include "perception/common/logging/logging.h"

namespace perception
{

OpenCVInferenceEngine::OpenCVInferenceEngine(const InferenceEngineParameters& params) : params_{params} {}

void OpenCVInferenceEngine::Init()
{
    net_ = cv::dnn::readNetFromTensorflow(params_.model_path, params_.model_proto);
    LOG(INFO) << "Successfully loaded saved model from '" << params_.model_path << "'.";
}

void OpenCVInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);
    UpdateTensors();
    UpdateOutputs();
}

void OpenCVInferenceEngine::Shutdown() {}

std::vector<cv::Mat> OpenCVInferenceEngine::GetResults() const
{
    return results_;
}

void OpenCVInferenceEngine::UpdateInput(const Image& image)
{
    cv::Mat input = cv::dnn::blobFromImage(image, params_.scale, params_.dim, params_.mean, params_.swap_rgb, false);
    net_.setInput(input, params_.input_tensor_name);
}

void OpenCVInferenceEngine::UpdateTensors()
{
    std::transform(output_tensor_names_.begin(),
                   output_tensor_names_.end(),
                   std::back_inserter(results_),
                   [](auto const& output_tensor_name) { return net_.forward(output_tensor_name); });
}

void OpenCVInferenceEngine::UpdateOutputs() {}

}  // namespace perception
