///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/inference_engine/torch_inference_engine.h"

#include "perception/common/logging/logging.h"

// #include <torch/torch.h>

namespace perception
{
TorchInferenceEngine::TorchInferenceEngine() {}

void TorchInferenceEngine::Init()
{
    // torch::Tensor tensor = torch::eye(3);
    // LOG(INFO) << "Successfully created tensor: " << tensor;
}

void TorchInferenceEngine::Execute(const Image& image) {}

void TorchInferenceEngine::Shutdown() {}

}  // namespace perception
