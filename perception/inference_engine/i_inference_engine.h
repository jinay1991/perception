///
/// @file
/// @brief Contains Inference Interface Engine definition
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H

#include <opencv4/opencv2/core.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace perception
{

using Image = cv::Mat;

/// @brief Inference Engine Interface class
class IInferenceEngine
{
  public:
    /// @brief Destructor
    virtual ~IInferenceEngine() = default;

    /// @brief Initialise Inference Engine
    virtual void Init() = 0;

    /// @brief Execute Inference with Inference Engine
    virtual void Execute(const Image& image) = 0;

    /// @brief Release Inference Engine
    virtual void Shutdown() = 0;
};

using InferenceEnginePtr = std::unique_ptr<IInferenceEngine>;

}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H
