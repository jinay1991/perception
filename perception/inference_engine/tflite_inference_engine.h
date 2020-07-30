///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H

#include "perception/datatypes/inference_engine_type.h"
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
class TFLiteInferenceEngine final : public IInferenceEngine
{
  public:
    /// @brief Constructor
    explicit TFLiteInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Destructor
    ~TFLiteInferenceEngine() = default;

    /// @brief Initialise TFLite Inference Engine
    void Init() override;

    /// @brief Execute Inference with TFLite Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release TFLite Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Model root directory
    const std::string model_path_;

    /// @brief TFLite Model Buffer Instance
    std::unique_ptr<tflite::FlatBufferModel> model_;

    /// @brief TFLite Model Interpreter instance
    std::unique_ptr<tflite::Interpreter> interpreter_;

    /// @brief Output Tensors saved as cv::Mat
    std::vector<cv::Mat> results_;
};

}  // namespace perception
#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TFLITE_INFERENCE_ENGINE_H
