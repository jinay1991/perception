///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/datatypes/camera.h"
#include "perception/datatypes/inference_engine_type.h"
#include "perception/datatypes/traffic_sign.h"
#include "perception/inference_engine/inference_engine_strategy.h"

namespace perception
{
/// @brief Performs Traffic Sign Recognition on received images
class TrafficSign final
{
  public:
    /// @brief Constructor
    TrafficSign();

    /// @brief Initialize Traffic Sign recognizer
    void Init();

    /// @brief Execute Single step (performs traffic sign recognise and updates traffic sign list buffer)
    void Step();

    /// @brief Release resources used for traffic sign recognizer
    void Shutdown();

    /// @brief Set Camera Message, containing captured images
    /// @param camera_message [in] - Camera captured image Message
    void SetCameraMessage(const CameraMessage& camera_message);

    /// @brief Provide Traffic Sign List based on identified traffic signs from the given Camera image
    const TrafficSignListMessage& GetTrafficSignListMessage() const;

  private:
    /// @brief Update Outputs (aka Traffic Sign)
    void UpdateOutputs();

    /// @brief Inference Engine related parameters (i.e. model path, model IO etc.)
    const InferenceEngineParameters inference_engine_params_;

    /// @brief Instance of Inference Engine (Default: TensorFlowInferenceEngine)
    InferenceEngineStrategy inference_engine_;

    /// @brief Received Camera Image message
    CameraMessage camera_message_;

    /// @brief List of identified Traffic Signs
    TrafficSignListMessage traffic_sign_list_message_;
};
}  // namespace perception
