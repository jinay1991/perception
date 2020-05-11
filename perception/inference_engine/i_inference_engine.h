///
/// @file
/// @brief Contains Inference Interface Engine definition
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H_
#define PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H_

#include <cstdint>
#include <string>
#include <vector>

namespace perception
{

/// @brief Inference Engine Interface class
class IInferenceEngine
{
  public:
    /// @brief Destructor
    virtual ~IInferenceEngine() = default;

    /// @brief Initialise Inference Engine
    virtual void Init() = 0;

    /// @brief Execute Inference with Inference Engine
    virtual void Execute() = 0;

    /// @brief Release Inference Engine
    virtual void Shutdown() = 0;
};

}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_I_INFERENCE_ENGINE_H_
