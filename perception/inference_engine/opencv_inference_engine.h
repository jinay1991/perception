///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_OPENCV_INFERENCE_ENGINE_H
#define PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_OPENCV_INFERENCE_ENGINE_H

#include "perception/datatypes/inference_engine_type.h"
#include "perception/inference_engine/i_inference_engine.h"

#include <opencv4/opencv2/dnn.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace perception
{
/// @brief OpenCV Inference Engine class
class OpenCVInferenceEngine final : public IInferenceEngine
{
  public:
    /// @brief Constructor
    /// @param params[in] - Inference Engine Parameters such as model input/output node names
    explicit OpenCVInferenceEngine(const InferenceEngineParameters& params);

    /// @brief Destructor
    virtual ~OpenCVInferenceEngine() = default;

    /// @brief Initialise TensorFlow Inference Engine
    void Init() override;

    /// @brief Execute Inference with TensorFlow Inference Engine
    /// @param image[in] - Image to be fed as input to Inference Engine
    void Execute(const Image& image) override;

    /// @brief Release TensorFlow Inference Engine
    void Shutdown() override;

    /// @brief Provide results in terms of Matrix
    /// @return List of results (aka cv::Mat) for requested outputs (will be in same order as output_node_names provided
    ///         in InferenceEngineParameters)
    std::vector<cv::Mat> GetResults() const override;

  private:
    /// @brief Updates Input Tensor by copying image to input_tensor
    /// @param image[in] - Input image to be fed to Inference Engine
    virtual void UpdateInput(const Image& image);

    /// @brief Updates Output Tensors by running the tensorflow session
    virtual void UpdateTensors();

    /// @brief Converts output_tensors to cv::Mat results
    virtual void UpdateOutputs();

    /// @brief Input Tensor name
    const std::string input_tensor_name_;

    /// @brief Output Tensors names
    const std::vector<std::string> output_tensor_names_;

    /// @brief Model root directory
    const InferenceEngineParameters& params_;

    /// @brief Output Tensors saved as cv::Mat
    std::vector<cv::Mat> results_;
};

}  // namespace perception

#endif  /// PERCEPTION_INFERENCE_ENGINE_INFERENCE_ENGINE_TF_INFERENCE_ENGINE_H
