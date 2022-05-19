///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/inference_engine/torch_inference_engine.h"

#include "perception/common/logging.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <algorithm>
#include <iterator>

namespace perception
{
namespace
{
/// @brief Converts matrix (aka cv::Mat) to torch::Tensor
///
/// @param matrix [in] matrix (aka cv::Mat)
///
/// @return Equivalent torch::Tensor for given image by copying the image contents to tensor.
torch::Tensor ConvertToTensor(const Image& image)
{
    auto tensor = torch::from_blob(image.data, {1, image.rows, image.cols, 3}, torch::kByte);
    tensor = tensor.permute({0, 3, 1, 2});  // convert to CxHxW
    tensor = tensor.to(torch::kF32);
    return tensor;
}

/// @brief Converts torch::Tensor to Image (aka cv::Mat)
///
/// @param tensor [in] torch::Tensor in [NxHxWxC form]
///
/// @return Equivalent image (aka cv::Mat) for given torch::Tensor by copying contents.
cv::Mat ConvertToMatrix(const torch::Tensor& tensor)
{
    const auto tensor_size = tensor.sizes();
    const auto rows = tensor.dim() > 1 ? static_cast<std::int32_t>(tensor_size[0]) : 1;
    const auto cols = tensor.dim() > 2 ? static_cast<std::int32_t>(tensor_size[1]) : 1;
    const auto channels = tensor.dim() > 3 ? static_cast<std::int32_t>(tensor_size[2]) : 1;
    auto* tensor_ptr = tensor.data_ptr();
    cv::Mat matrix{rows, cols, CV_32FC(channels), tensor_ptr};
    return matrix;
}
}  // namespace

TorchInferenceEngine::TorchInferenceEngine(const InferenceEngineParameters& params)
    : net_{},
      input_tensor_{},
      input_tensor_name_{params.input_tensor_name},
      output_tensors_{},
      output_tensor_names_{params.output_tensor_names},
      model_path_{params.model_path},
      results_{}
{
}

void TorchInferenceEngine::Init()
{
    net_ = torch::jit::load(model_path_);
}

void TorchInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);
    UpdateTensors();
    UpdateOutputs();
}

void TorchInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TorchInferenceEngine::GetResults() const
{
    return results_;
}

void TorchInferenceEngine::UpdateInput(const Image& image)
{
    cv::Mat resized_image{};
    cv::resize(image, resized_image, cv::Size(300, 300));
    input_tensor_ = ConvertToTensor(resized_image);
}

void TorchInferenceEngine::UpdateTensors()
{
    const std::vector<torch::jit::IValue> inputs{{input_tensor_}};
    const auto outputs = net_.forward(inputs);
    const auto outputs_tuple = outputs.toTuple();
    const auto outputs_elements = outputs_tuple->elements();
    std::transform(outputs_elements.cbegin(),
                   outputs_elements.cend(),
                   std::back_inserter(output_tensors_),
                   [](const auto& output) { return output.toTensor(); });

    LOG(INFO) << "Successfully received results " << output_tensors_.size() << " outputs.";
}

void TorchInferenceEngine::UpdateOutputs()
{
    std::transform(output_tensors_.cbegin(),
                   output_tensors_.cend(),
                   std::back_inserter(results_),
                   [](auto const& tensor) { return ConvertToMatrix(tensor); });
}
}  // namespace perception
