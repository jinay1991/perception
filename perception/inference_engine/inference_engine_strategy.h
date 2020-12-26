///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_STRATEGY_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_STRATEGY_H

#include "perception/datatypes/inference_engine_type.h"
#include "perception/inference_engine/i_inference_engine.h"

#include <memory>

namespace perception
{

/// @brief Inference Engine Strategy
class InferenceEngineStrategy final
{
  public:
    /// @brief Default Constructor
    InferenceEngineStrategy();

    /// @brief Initialise Inference Engine
    void Init();

    /// @brief Execute Inference with Inference Engine
    void Execute(const Image& image);

    /// @brief Release Inference Engine
    void Shutdown();

    /// @brief Select Inference Engine
    /// @param inference_engine_type  [in] Inference Engine type (TF, TFLite)
    void SelectInferenceEngine(const InferenceEngineType& inference_engine_type,
                               const InferenceEngineParameters& inference_engine_parameters);

    /// @brief Provide results from Inference Engine
    std::vector<cv::Mat> GetResults() const;

    /// @brief Provide selected inference engine type
    /// @return InferenceEngineType
    InferenceEngineType GetInferenceEngineType() const;

  private:
    /// @brief Inference Engine
    std::unique_ptr<IInferenceEngine> inference_engine_;

    /// @brief Inference Engine Type
    InferenceEngineType inference_engine_type_;
};
}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_STRATEGY_H
