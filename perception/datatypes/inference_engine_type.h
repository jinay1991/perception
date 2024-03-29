///
/// @file
/// @copyright Copyright (c) 2023. MIT License
///
#ifndef PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_TYPE_H
#define PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_TYPE_H

#include <opencv4/opencv2/core.hpp>

#include <ostream>
#include <string>

namespace perception
{
/// @brief List of Inference Engine supported
enum class InferenceEngineType : std::uint8_t
{
    kTensorFlowLite = 0U,
    kTensorFlow = 1U,
    kTorch = 2U,
    kOpenCV = 3U,
    kInvalid = 255U
};

/// @brief InferenceEngine Parameters
struct InferenceEngineParameters
{
    /// @brief Path to Model
    std::string model_path{};

    /// @brief Input Node/Tensor Name
    std::string input_tensor_name{};

    /// @brief List of Output Nodes/Tensors Name
    std::vector<std::string> output_tensor_names{};

    /// @brief Path to Model configurations
    std::string config_path{};
};

inline const char* to_string(const InferenceEngineType& inference_engine_type)
{
    switch (inference_engine_type)
    {
        case InferenceEngineType::kTensorFlow:
            return "kTensorFlow";
        case InferenceEngineType::kTensorFlowLite:
            return "kTensorFlowLite";
        case InferenceEngineType::kTorch:
            return "kTorch";
        case InferenceEngineType::kOpenCV:
            return "kOpenCV";
        default:
            return "ERROR: Unknown InferenceEngineType.";
    }
    return "ERROR: Unknown InferenceEngineType.";
}

inline std::ostream& operator<<(std::ostream& stream, const InferenceEngineType& inference_engine_type)
{
    const char* name = to_string(inference_engine_type);
    stream << name;
    return stream;
}

}  // namespace perception
#endif  /// PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_H
