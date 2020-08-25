///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tflite_inference_engine.h"

#include "perception/common/logging/logging.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"

namespace perception
{

TFLiteInferenceEngine::TFLiteInferenceEngine(const InferenceEngineParameters& params)
    : model_path_{params.model_path}, results_{}
{
}

void TFLiteInferenceEngine::Init()
{
    model_ = tflite::FlatBufferModel::BuildFromFile(model_path_.c_str());
    ASSERT_CHECK(model_) << "Failed to read model " << model_path_;
    model_->error_reporter();

    tflite::ops::builtin::BuiltinOpResolver resolver{};

    tflite::InterpreterBuilder(*model_, resolver)(&interpreter_);
    ASSERT_CHECK(interpreter_) << "Failed to construct interpreter";

    ASSERT_CHECK_EQ(interpreter_->AllocateTensors(), TfLiteStatus::kTfLiteOk) << "Failed to allocate tensors!";
}

void TFLiteInferenceEngine::Execute(const Image& image)
{
    interpreter_->Invoke();
}

void TFLiteInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TFLiteInferenceEngine::GetResults() const
{
    return results_;
}

}  // namespace perception
