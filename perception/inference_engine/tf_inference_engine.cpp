///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tf_inference_engine.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/core/hal/interface.h>

#include <unordered_set>

namespace perception
{

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
    ASSERT_CHECK(ret.ok()) << "Failed to load saved model '" << model_path_ << "', (Message: " << ret.error_message()
                           << ")";

    LOG(INFO) << "Successfully loaded saved model from '" << model_path_ << "'.";
}

void TFInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);

    const std::vector<std::pair<std::string, tensorflow::Tensor>> inputs{{input_tensor_name_, input_tensor_}};
    const std::vector<std::string> target_node_names{};
    const auto ret = bundle_->GetSession()->Run(inputs, output_tensor_names_, target_node_names, &output_tensors_);
    ASSERT_CHECK(ret.ok()) << "Unable to run Session, (Message: " << ret.error_message() << ")";

    LOG(INFO) << "Successfully received results " << output_tensors_.size() << " outputs.";

    UpdateOutputs();
}

void TFInferenceEngine::Shutdown() {}

std::vector<cv::Mat> TFInferenceEngine::GetResults() const
{
    return results_;
}

void TFInferenceEngine::UpdateInput(const Image& image)
{
    input_tensor_ =
        tensorflow::Tensor{tensorflow::DT_UINT8, tensorflow::TensorShape{1, image.rows, image.cols, image.channels()}};
    auto* input_tensor_ptr = input_tensor_.flat<tensorflow::uint8>().data();
    Image tensor_image{image.rows, image.cols, CV_8UC3, input_tensor_ptr};
    image.convertTo(tensor_image, CV_8UC3);
}

void TFInferenceEngine::UpdateOutputs()
{
    std::vector<cv::Mat> tensor_matrices{};
    for (auto idx = 0; idx < output_tensors_.size(); ++idx)
    {
        auto tensor = output_tensors_.at(idx);
        const auto cols = static_cast<std::int32_t>(tensor.dim_size(0));
        const auto rows = static_cast<std::int32_t>(tensor.dim_size(1));
        const auto channels = tensor.dims() > 2 ? static_cast<std::int32_t>(tensor.dim_size(2)) : 1;
        const auto* tensor_ptr = tensor.flat<float>().data();
        cv::Mat tensor_matrix{rows, cols, CV_32FC(channels), &tensor_ptr};

        tensor_matrices.push_back(tensor_matrix);
    }

    results_ = tensor_matrices;
}

}  // namespace perception
