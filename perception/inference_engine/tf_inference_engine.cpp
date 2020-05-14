///
/// @file
/// @copyright Copyright (c) 2020. All Rights Reserved.
///
#include "perception/inference_engine/tf_inference_engine.h"

#include "perception/common/logging/logging.h"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace perception
{

TFInferenceEngine::TFInferenceEngine()
    : bundle_{std::make_shared<tensorflow::SavedModelBundle>()},
      input_tensor_{},
      output_tensors_{},
      output_tensor_names_{"strided_slice_18", "strided_slice_38"},
      model_dir_{"external/models/"}
{
}

void TFInferenceEngine::Init()
{
    tensorflow::SessionOptions session_options{};
    tensorflow::RunOptions run_options{};
    std::unordered_set<std::string> tags{"serve"};

    const auto ret = tensorflow::LoadSavedModel(session_options, run_options, model_dir_, tags, bundle_.get());
    ASSERT_CHECK(ret.ok()) << "Failed to load saved model";
}

void TFInferenceEngine::Execute()
{
    auto inputs = std::vector<std::pair<std::string, tensorflow::Tensor>>{{"Placeholder", input_tensor_}};
    auto target_node_names = std::vector<std::string>{};
    auto outputs = std::vector<tensorflow::Tensor>{};
    auto status = bundle_->GetSession()->Run(inputs, output_tensor_names_, target_node_names, &outputs);
    ASSERT_CHECK(status.ok()) << "Unable to run Session, (Returned: " << status.ok() << ")";

    LOG(INFO) << "Successfully received split " << outputs.size() << " waves.";

    /// Extract results
    // auto waveforms = Waveforms{};
    // std::transform(
    //     outputs.begin(), outputs.end(), std::back_inserter(waveforms), [&](const tensorflow::Tensor& tensor) {
    //         auto waveform = Waveform{};
    //         waveform.resize(input_tensor_.dim_size(0) * input_tensor_.dim_size(1));

    //         auto tensor_dataptr = tensor.matrix<float>().data();
    //         std::copy(tensor_dataptr, tensor_dataptr + waveform.size(), waveform.begin());
    //         return waveform;
    //     });

    // results_ = waveforms;
}

void TFInferenceEngine::Shutdown() {}

}  // namespace perception