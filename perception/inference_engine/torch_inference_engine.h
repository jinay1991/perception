///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H

#include "perception/datatypes/inference_engine_type.h"
#include "perception/inference_engine/i_inference_engine.h"

#include <torch/script.h>
#include <torch/torch.h>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace perception
{
class TorchInferenceEngine final : public IInferenceEngine
{
  public:
    /// @brief Constructor
    /// @param params [in] Inference Engine Parameters such as model input/output node names
    explicit TorchInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Initialise Inference Engine
    void Init() override;

    /// @brief Execute Inference with Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Updates Input Tensor by copying image to input_tensor
    /// @param image [in] Input image to be fed to Inference Engine
    void UpdateInput(const Image& image);

    /// @brief Updates Output Tensors by running the tensorflow session
    void UpdateTensors();

    /// @brief Converts output_tensors to cv::Mat results
    void UpdateOutputs();

    /// @brief Model object
    torch::jit::Module net_;

    /// @brief Input Tensor
    torch::Tensor input_tensor_;

    /// @brief Input Tensor name
    const std::string input_tensor_name_;

    /// @brief Output Tensors
    std::vector<at::Tensor> output_tensors_;

    /// @brief Output Tensors names
    const std::vector<std::string> output_tensor_names_;

    /// @brief Model root directory
    const std::string model_path_;

    /// @brief Output Tensors saved as cv::Mat
    std::vector<cv::Mat> results_;
};
}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
