///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_TYPE_H_
#define PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_TYPE_H_

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
    kInvalid = 255U
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
#endif  /// PERCEPTION_COMMON_DATATYPE_INFERENCE_ENGINE_H_