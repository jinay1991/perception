///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tflite_inference_engine.h"

#include "perception/common/logging/logging.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include <sys/time.h>

#include <algorithm>
#include <string>

namespace perception
{

TFLiteInferenceEngine::TFLiteInferenceEngine() {}

void TFLiteInferenceEngine::Init()
{
    const std::string model_path{};
    model_ = tflite::FlatBufferModel::BuildFromFile(model_path.c_str());
    ASSERT_CHECK(model_) << "Failed to mmap model " << model_path;
    model_->error_reporter();

    tflite::ops::builtin::BuiltinOpResolver resolver;

    tflite::InterpreterBuilder(*model_, resolver)(&interpreter_);
    ASSERT_CHECK(interpreter_) << "Failed to construct interpreter";

    ASSERT_CHECK_EQ(interpreter_->AllocateTensors(), TfLiteStatus::kTfLiteOk) << "Failed to allocate tensors!";

    PrintInterpreterState(interpreter_.get());
}

void TFLiteInferenceEngine::Execute(const Image& image)
{
    interpreter_->Invoke();
}

void TFLiteInferenceEngine::Shutdown() {}

}  // namespace perception
