///
/// @file
/// @copyright Copyright (c) 2023. MIT License
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
class TFInferenceEngine final : public IInferenceEngine
{
  public:
    /// @brief Constructor
    ///
    /// @param params [in] Inference Engine Parameters such as model input/output node names
    explicit TFInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Initialise TensorFlow Inference Engine
    void Init() override;

    /// @brief Execute Inference with TensorFlow Inference Engine
    ///
    /// @param image [in] Image to be fed as input to Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release TensorFlow Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    ///
    /// @return List of results (aka cv::Mat) for requested outputs (will be in same order as output_node_names provided
    ///         in InferenceEngineParameters)
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Updates Input Tensor by copying image to input_tensor
    ///
    /// @param image [in] Input image to be fed to Inference Engine
    void UpdateInput(const Image& image);

    /// @brief Updates Output Tensors by running the tensorflow session
    void UpdateTensors();

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
    std::vector<cv::Mat> results_;
};

}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TF_INFERENCE_ENGINE_H
