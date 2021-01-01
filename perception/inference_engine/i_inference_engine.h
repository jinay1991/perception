///
/// @file
/// @brief Contains Inference Interface Engine definition
/// @copyright Copyright (c) 2020-2021. MIT License
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
    /// @param image [in] Image to be fed as input to Inference Engine
    virtual void Execute(const Image& image) = 0;

    /// @brief Release Inference Engine
    virtual void Shutdown() = 0;

    /// @brief Provide results in terms of Matrix
    /// @return List of results (aka cv::Mat) for requested outputs (will be in same order as output_node_names provided
    ///         in InferenceEngineParameters)
    virtual std::vector<cv::Mat> GetResults() const = 0;
};

/// @brief InferenceEngine unique instance pointer
using InferenceEnginePtr = std::unique_ptr<IInferenceEngine>;

}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H
