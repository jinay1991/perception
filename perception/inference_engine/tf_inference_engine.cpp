///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tf_inference_engine.h"

#include "perception/common/logging.h"

#include <unordered_set>

namespace perception
{
namespace
{
/// @brief Converts tensorflow::Tensor to Image (aka cv::Mat)
///
/// @param tensor[in] tensorflow::Tensor in [NxHxWxC form]
///
/// @return Equivalent image (aka cv::Mat) for given tensorflow::Tensor by copying contents.
cv::Mat ConvertToMatrix(const tensorflow::Tensor& tensor)
{
    tensorflow::Tensor tensor_matrix = tensor;
    const auto rows = tensor_matrix.dims() > 1 ? static_cast<std::int32_t>(tensor_matrix.dim_size(1)) : 1;
    const auto cols = tensor_matrix.dims() > 2 ? static_cast<std::int32_t>(tensor_matrix.dim_size(2)) : 1;
    const auto channels = tensor_matrix.dims() > 3 ? static_cast<std::int32_t>(tensor_matrix.dim_size(3)) : 1;
    auto* tensor_ptr = tensor_matrix.flat<float>().data();
    cv::Mat matrix{rows, cols, CV_32FC(channels), tensor_ptr};
    return matrix;
}

/// @brief Converts matrix (aka cv::Mat) to tensorflow::Tensor
///
/// @param matrix[in] matrix (aka cv::Mat)
///
/// @return Equivalent tensorflow::Tensor for given image by copying the image contents to tensor.
tensorflow::Tensor ConvertToTensor(const cv::Mat& matrix)
{
    tensorflow::Tensor tensor{tensorflow::DT_UINT8,
                              tensorflow::TensorShape{1, matrix.rows, matrix.cols, matrix.channels()}};
    auto* tensor_ptr = tensor.flat<tensorflow::uint8>().data();
    cv::Mat tensor_matrix{matrix.rows, matrix.cols, CV_8UC3, tensor_ptr};
    matrix.convertTo(tensor_matrix, CV_8UC3);
    return tensor;
}
}  // namespace

TFInferenceEngine::TFInferenceEngine(const InferenceEngineParameters& params)
    : bundle_{std::make_shared<tensorflow::SavedModelBundle>()},
      input_tensor_{},
      input_tensor_name_{params.input_tensor_name},
      output_tensors_{},
      output_tensor_names_{params.output_tensor_names},
      model_path_{params.model_path}
{
}

void TFInferenceEngine::Init()
{
    tensorflow::SessionOptions session_options{};
    tensorflow::RunOptions run_options{};
    std::unordered_set<std::string> tags{"serve"};

    const auto ret = tensorflow::LoadSavedModel(session_options, run_options, model_path_, tags, bundle_.get());
    CHECK(ret.ok()) << "Failed to load saved model '" << model_path_ << "', (Message: " << ret.error_message() << ")";

    LOG(INFO) << "Successfully loaded saved model from '" << model_path_ << "'.";
}

void TFInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);
    UpdateTensors();
    UpdateOutputs();
}

void TFInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TFInferenceEngine::GetResults() const
{
    return results_;
}

void TFInferenceEngine::UpdateInput(const Image& image)
{
    input_tensor_ = ConvertToTensor(image);
}

void TFInferenceEngine::UpdateTensors()
{
    const std::vector<std::pair<std::string, tensorflow::Tensor>> inputs{{input_tensor_name_, input_tensor_}};
    const std::vector<std::string> target_node_names{};

    const auto ret = bundle_->GetSession()->Run(inputs, output_tensor_names_, target_node_names, &output_tensors_);
    CHECK(ret.ok()) << "Unable to run Session, (Message: " << ret.error_message() << ")";

    LOG(INFO) << "Successfully received results " << output_tensors_.size() << " outputs.";
}

void TFInferenceEngine::UpdateOutputs()
{
    std::transform(
        output_tensors_.cbegin(), output_tensors_.cend(), std::back_inserter(results_), [](auto const& tensor) {
            return ConvertToMatrix(tensor);
        });
}

}  // namespace perception
