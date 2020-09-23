///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/null_inference_engine.h"

#include "perception/common/logging/logging.h"

namespace perception
{

NullInferenceEngine::NullInferenceEngine(const InferenceEngineParameters& params)
    : results_{params.output_tensor_names.size()}
{
}

void NullInferenceEngine::Init() {}

void NullInferenceEngine::Execute(const Image& image) {}

void NullInferenceEngine::Shutdown() {}

std::vector<cv::Mat> NullInferenceEngine::GetResults() const
{
    return results_;
}

}  // namespace perception
