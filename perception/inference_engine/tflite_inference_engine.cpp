///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tflite_inference_engine.h"

#include "perception/common/logging/logging.h"
#include "tensorflow/lite/builtin_op_data.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

namespace perception
{
namespace
{
/// @brief Resize Provided Image using TFLite Interpreter
template <class T>
void ResizeImage(T* out,
                 const std::uint8_t* in,
                 const std::int32_t image_height,
                 const std::int32_t image_width,
                 const std::int32_t image_channels,
                 const std::int32_t wanted_height,
                 const std::int32_t wanted_width,
                 const std::int32_t wanted_channels,
                 const bool input_floating,
                 const float input_mean,
                 const float input_std)
{
    std::int32_t number_of_pixels = image_height * image_width * image_channels;
    std::unique_ptr<tflite::Interpreter> interpreter = std::make_unique<tflite::Interpreter>();

    std::int32_t base_index = 0;

    // two inputs: input and new_sizes
    interpreter->AddTensors(2, &base_index);
    // one output
    interpreter->AddTensors(1, &base_index);
    // set input and output tensors
    interpreter->SetInputs({0, 1});
    interpreter->SetOutputs({2});

    // set parameters of tensors
    TfLiteQuantizationParams quant;
    interpreter->SetTensorParametersReadWrite(
        0, kTfLiteFloat32, "input", {1, image_height, image_width, image_channels}, quant);
    interpreter->SetTensorParametersReadWrite(1, kTfLiteInt32, "new_size", {2}, quant);
    interpreter->SetTensorParametersReadWrite(
        2, kTfLiteFloat32, "output", {1, wanted_height, wanted_width, wanted_channels}, quant);

    tflite::ops::builtin::BuiltinOpResolver resolver;
    const TfLiteRegistration* resize_op = resolver.FindOp(tflite::BuiltinOperator_RESIZE_BILINEAR, 1);
    auto* params = reinterpret_cast<TfLiteResizeBilinearParams*>(malloc(sizeof(TfLiteResizeBilinearParams)));
    params->align_corners = false;
    interpreter->AddNodeWithParameters({0, 1}, {2}, nullptr, 0, params, resize_op, nullptr);

    interpreter->AllocateTensors();

    // fill input image
    // in[] are integers, cannot do memcpy() directly
    auto input = interpreter->typed_tensor<float>(0);
    for (std::int32_t i = 0; i < number_of_pixels; i++)
    {
        input[i] = in[i];
    }

    // fill new_sizes
    interpreter->typed_tensor<std::int32_t>(1)[0] = wanted_height;
    interpreter->typed_tensor<std::int32_t>(1)[1] = wanted_width;

    interpreter->Invoke();

    auto output = interpreter->typed_tensor<float>(2);
    auto output_number_of_pixels = wanted_height * wanted_width * wanted_channels;

    for (std::int32_t i = 0; i < output_number_of_pixels; i++)
    {
        if (input_floating)
        {
            out[i] = (output[i] - input_mean) / input_std;
        }
        else
        {
            out[i] = static_cast<std::uint8_t>(output[i]);
        }
    }
}
}  // namespace

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

    LOG(INFO) << "Successfully loaded tflite model from '" << model_path_ << "'.";
}

void TFLiteInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);
    UpdateTensors();
    UpdateOutputs();
}

void TFLiteInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TFLiteInferenceEngine::GetResults() const
{
    return results_;
}

void TFLiteInferenceEngine::UpdateInput(const Image& image)
{
    const auto input = interpreter_->inputs()[0];

    TfLiteIntArray* dims = interpreter_->tensor(input)->dims;
    const auto wanted_height = dims->data[1];
    const auto wanted_width = dims->data[2];
    const auto wanted_channels = dims->data[3];
    const auto mean = 1.0;
    const auto stddev = 0.0;

    switch (interpreter_->tensor(input)->type)
    {
        case TfLiteType::kTfLiteFloat32:
        {
            ResizeImage<float>(interpreter_->typed_tensor<float>(input),
                               image.data,
                               image.rows,
                               image.cols,
                               image.channels(),
                               wanted_height,
                               wanted_width,
                               wanted_channels,
                               true,
                               mean,
                               stddev);
            break;
        }
        case TfLiteType::kTfLiteUInt8:
        {
            ResizeImage<std::uint8_t>(interpreter_->typed_tensor<std::uint8_t>(input),
                                      image.data,
                                      image.rows,
                                      image.cols,
                                      image.channels(),
                                      wanted_height,
                                      wanted_width,
                                      wanted_channels,
                                      true,
                                      mean,
                                      stddev);
            break;
        }
        default:
        {
            LOG(ERROR) << "Cannot handle input type " << interpreter_->tensor(input)->type << " yet";
            break;
        }
    }
}

void TFLiteInferenceEngine::UpdateTensors()
{
    const auto ret = interpreter_->Invoke();
    ASSERT_CHECK_EQ(ret, TfLiteStatus::kTfLiteOk) << "Failed to invoke tflite!";
}

void TFLiteInferenceEngine::UpdateOutputs()
{
    const auto output = interpreter_->outputs()[0];
    const auto output_dims = interpreter_->tensor(output)->dims;
    const auto output_size = output_dims->data[output_dims->size - 1];

    results_.resize(output_size);

    /// @todo Update results with inference output
}

}  // namespace perception
