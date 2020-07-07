///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TF_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TF_INFERENCE_ENGINE_H

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
/// @brief TensorFlow Inference Engine class
class TFInferenceEngine : public IInferenceEngine
{
  public:
    /// @brief Constructor
    explicit TFInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Destructor
    ~TFInferenceEngine() = default;

    /// @brief Initialise TensorFlow Inference Engine
    void Init() override;

    /// @brief Execute Inference with TensorFlow Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release TensorFlow Inference Engine
    void Shutdown() override;

    cv::Mat GetResults() const;

  private:
    /// @brief Updates Input Tensor by copying image to input_tensor_
    void UpdateInput(const Image& image);

    /// @brief Converts output_tensors to cv::Mat results
    void UpdateOutputs();

    /// @brief Saved Model bundle
    std::shared_ptr<tensorflow::SavedModelBundle> bundle_;

    /// @brief Input Tensor
    tensorflow::Tensor input_tensor_;

    /// @brief Input Tensor name
    const std::string input_tensor_name_;

    /// @brief Output Tensors
    std::vector<tensorflow::Tensor> output_tensors_;

    /// @brief Output Tensors names
    const std::vector<std::string> output_tensor_names_;

    /// @brief Model root directory
    const std::string model_path_;

    /// @brief Output Tensors saved as cv::Mat
    cv::Mat results_;
};

}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TF_INFERENCE_ENGINE_H
