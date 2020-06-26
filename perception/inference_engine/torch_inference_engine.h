///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H

#include "perception/inference_engine/i_inference_engine.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace perception
{
class TorchInferenceEngine : public IInferenceEngine
{
  public:
    /// @brief Default Constructor
    TorchInferenceEngine();

    /// @brief Destructor
    ~TorchInferenceEngine() = default;

    /// @brief Initialise Inference Engine
    void Init() override;

    /// @brief Execute Inference with Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release Inference Engine
    void Shutdown() override;
};
}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TORCH_INFERENCE_ENGINE_H
