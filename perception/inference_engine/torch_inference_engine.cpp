///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/inference_engine/torch_inference_engine.h"

#include "perception/common/logging/logging.h"

#include <torch/torch.h>

namespace perception
{
TorchInferenceEngine::TorchInferenceEngine(const InferenceEngineParameters& /* params */) : results_{} {}

void TorchInferenceEngine::Init() {}

void TorchInferenceEngine::Execute(const Image& image) {}

void TorchInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TorchInferenceEngine::GetResults() const
{
    return results_;
}

}  // namespace perception
