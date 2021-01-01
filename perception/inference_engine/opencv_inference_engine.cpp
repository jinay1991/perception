///
/// @file
/// @copyright Copyright (c) 2020-2021. All Rights Reserved.
///
#include "perception/inference_engine/opencv_inference_engine.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/imgproc.hpp>

namespace perception
{
OpenCVInferenceEngine::OpenCVInferenceEngine(const InferenceEngineParameters& params)
    : net_{},
      input_tensor_{},
      input_tensor_name_{params.input_tensor_name},
      output_tensors_{},
      output_tensor_names_{params.output_tensor_names},
      model_path_{params.model_path},
      config_path_{params.config_path}
{
}

void OpenCVInferenceEngine::Init()
{
    net_ = cv::dnn::readNet(model_path_, config_path_);
    CHECK(!net_.empty()) << "Failed to load opencv model '" << model_path_ << "'";
    LOG(INFO) << "Successfully loaded opencv model from '" << model_path_ << "'.";
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
    input_tensor_ = cv::dnn::blobFromImage(image);
    net_.setInput(input_tensor_, input_tensor_name_);
}

void OpenCVInferenceEngine::UpdateTensors()
{
    net_.forward(output_tensors_, output_tensor_names_);
    LOG(INFO) << "Successfully received results " << output_tensors_.size() << " outputs.";

    /// @todo Why output_tensors_ does not contain any bbox?
}

void OpenCVInferenceEngine::UpdateOutputs()
{
    std::copy(output_tensors_.cbegin(), output_tensors_.cend(), std::back_inserter(results_));
}

}  // namespace perception
