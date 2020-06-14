///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H

#include "perception/inference_engine/i_inference_engine.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace perception
{
/// @brief TFLite Inference Engine class
class TFLiteInferenceEngine : public IInferenceEngine
{
  public:
    /// @brief Default Constructor
    TFLiteInferenceEngine();

    /// @brief Destructor
    ~TFLiteInferenceEngine() = default;

    /// @brief Initialise TFLite Inference Engine
    void Init() override;

    /// @brief Execute Inference with TFLite Inference Engine
    void Execute() override;

    /// @brief Release TFLite Inference Engine
    void Shutdown() override;

  private:
    /// @brief TFLite Model Buffer Instance
    std::unique_ptr<tflite::FlatBufferModel> model_;

    /// @brief TFLite Model Interpreter instance
    std::unique_ptr<tflite::Interpreter> interpreter_;
};

}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H
