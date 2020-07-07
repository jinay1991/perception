///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tf_inference_engine.h"

#include "perception/common/logging/logging.h"

#include <unordered_set>

namespace perception
{

TFInferenceEngine::TFInferenceEngine(const InferenceEngineParameters& params)
    : bundle_{std::make_shared<tensorflow::SavedModelBundle>()},
      input_tensor_{},
      input_tensor_name_{params.input_tensor_name},
      output_tensors_{},
      output_tensor_names_{params.output_tensor_names},
      model_dir_{params.model_path}
{
}

void TFInferenceEngine::Init()
{
    tensorflow::SessionOptions session_options{};
    tensorflow::RunOptions run_options{};
    std::unordered_set<std::string> tags{"serve"};

    const auto ret = tensorflow::LoadSavedModel(session_options, run_options, model_dir_, tags, bundle_.get());
    ASSERT_CHECK(ret.ok()) << "Failed to load saved model '" << model_dir_ << "', (Message: " << ret.error_message()
                           << ")";

    LOG(INFO) << "Successfully loaded saved model from '" << model_dir_ << "'.";
}

void TFInferenceEngine::Execute(const Image& image)
{
    UpdateInput(image);

    std::vector<std::pair<std::string, tensorflow::Tensor>> inputs{{input_tensor_name_, input_tensor_}};
    std::vector<std::string> target_node_names{};
    auto status = bundle_->GetSession()->Run(inputs, output_tensor_names_, target_node_names, &output_tensors_);
    ASSERT_CHECK(status.ok()) << "Unable to run Session, (Message: " << status.error_message() << ")";

    LOG(INFO) << "Successfully received results " << output_tensors_.size() << " outputs.";
    LOG(INFO) << "output_tensors_.at(0): " << output_tensors_.at(0U).DebugString() << std::endl;

    UpdateOutputs();
}

void TFInferenceEngine::Shutdown() {}

cv::Mat TFInferenceEngine::GetResults() const
{
    return results_;
}

void TFInferenceEngine::UpdateInput(const Image& image)
{
    input_tensor_ =
        tensorflow::Tensor{tensorflow::DT_UINT8, tensorflow::TensorShape{1, image.rows, image.cols, image.channels()}};
    auto input_tensor_ptr = input_tensor_.flat<tensorflow::uint8>().data();
    Image tensor_image{image.rows, image.cols, CV_8UC3, input_tensor_ptr};
    image.convertTo(tensor_image, CV_8UC3);
}

void TFInferenceEngine::UpdateOutputs()
{
    std::vector<Image> tensor_images{output_tensors_.size()};
    // for (auto idx = 0; idx < tensor_images.size(); ++idx)
    // {
    //     auto output_tensor_ptr = output_tensors_.at(idx).flat<tensorflow::uint8>().data();
    // }
}

}  // namespace perception
