///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/inference_engine/inference_engine_strategy.h"

#include "perception/common/logging/logging.h"
#include "perception/inference_engine/null_inference_engine.h"
#include "perception/inference_engine/opencv_inference_engine.h"
#include "perception/inference_engine/tf_inference_engine.h"
#include "perception/inference_engine/tflite_inference_engine.h"
#include "perception/inference_engine/torch_inference_engine.h"

namespace perception
{

InferenceEngineStrategy::InferenceEngineStrategy() : inference_engine_type_{InferenceEngineType::kInvalid} {}

void InferenceEngineStrategy::SelectInferenceEngine(const InferenceEngineType& inference_engine_type,
                                                    const InferenceEngineParameters& inference_engine_parameters)
{
    inference_engine_type_ = inference_engine_type;
    switch (inference_engine_type)
    {
        case InferenceEngineType::kTensorFlow:
        {
            inference_engine_ = std::make_unique<TFInferenceEngine>(inference_engine_parameters);
            break;
        }
        case InferenceEngineType::kTensorFlowLite:
        {
            inference_engine_ = std::make_unique<TFLiteInferenceEngine>(inference_engine_parameters);
            break;
        }
        case InferenceEngineType::kTorch:
        {
            inference_engine_ = std::make_unique<TorchInferenceEngine>(inference_engine_parameters);
            break;
        }
        case InferenceEngineType::kOpenCV:
        {
            inference_engine_ = std::make_unique<OpenCVInferenceEngine>(inference_engine_parameters);
            break;
        }
        case InferenceEngineType::kInvalid:
        default:
        {
            inference_engine_ = std::make_unique<NullInferenceEngine>(inference_engine_parameters);
            LOG(FATAL) << "Received " << inference_engine_type;
            break;
        }
    }
}

void InferenceEngineStrategy::Init()
{
    inference_engine_->Init();
}

void InferenceEngineStrategy::Execute(const Image& image)
{
    inference_engine_->Execute(image);
}

void InferenceEngineStrategy::Shutdown()
{
    inference_engine_->Shutdown();
}

std::vector<cv::Mat> InferenceEngineStrategy::GetResults() const
{
    return inference_engine_->GetResults();
}

InferenceEngineType InferenceEngineStrategy::GetInferenceEngineType() const
{
    return inference_engine_type_;
}
}  // namespace perception
