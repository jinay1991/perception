///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H

#include "perception/datatypes/inference_engine_type.h"
#include "perception/inference_engine/i_inference_engine.h"

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
    /// @param params[in] Inference Engine Parameters such as model input/output node names
    explicit TorchInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Destructor
    ~TorchInferenceEngine() = default;

    /// @brief Initialise Inference Engine
    void Init() override;

    /// @brief Execute Inference with Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Output Tensors saved as cv::Mat
    std::vector<cv::Mat> results_;
};
}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
