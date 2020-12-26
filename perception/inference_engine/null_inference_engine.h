///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_NULL_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_NULL_INFERENCE_ENGINE_H

#include "perception/datatypes/inference_engine_type.h"
#include "perception/inference_engine/i_inference_engine.h"

#include <tensorflow/cc/client/client_session.h>
#include <tensorflow/cc/saved_model/loader.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace perception
{
/// @brief Null Inference Engine class
class NullInferenceEngine final : public IInferenceEngine
{
  public:
    /// @brief Constructor
    /// @param params [in] Inference Engine Parameters such as model input/output node names
    explicit NullInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Initialise Null Inference Engine
    void Init() override;

    /// @brief Execute Inference with Null Inference Engine
    /// @param image [in] Image to be fed as input to Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release Null Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    /// @return List of results (aka cv::Mat) for requested outputs (will be in same order as output_node_names provided
    ///         in InferenceEngineParameters)
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Output Tensors saved as cv::Mat
    const std::vector<cv::Mat> results_;
};

}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_NULL_INFERENCE_ENGINE_H
