///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_OBJECT_OBJECT_H
#define PERCEPTION_OBJECT_OBJECT_H

#include "perception/datatypes/camera.h"
#include "perception/datatypes/object.h"
#include "perception/inference_engine/inference_engine_strategy.h"

#include <opencv4/opencv2/core.hpp>

#include <string>

namespace perception
{
/// @brief Performs Object Detection on received images
class Object final
{
  public:
    /// @brief Constructor
    Object();

    /// @brief Initialize Object Detection
    void Init();

    /// @brief Execute Single step (performs object detections and updates object list buffer)
    void Step();

    /// @brief Release resources used for Object Detection
    void Shutdown();

    /// @brief Set Vehicle velocity
    /// @param ego_velocity [in] - Vehicle Velocity (mps)
    void SetEgoVelocity(const units::velocity::meters_per_second_t& ego_velocity);

    /// @brief Set Camera Message, containing captured images
    /// @param camera_message [in] - Camera captured image Message
    void SetCameraMessage(const CameraMessage& camera_message);

    /// @brief Provide Object List based on identified objects from the given Camera image
    const ObjectListMessage& GetObjectListMessage() const;

  private:
    /// @brief Update Outputs (aka Object List)
    void UpdateOutputs();

    /// @brief Computes Rotation and Translation Matrices for given Bounding Box
    ///
    /// @param bounding_box [in] Object Bounding Box (Result of object detection)
    /// @param rows [in] Camera Image Rows
    /// @param cols [in] Camera Image Columns
    /// @param rotational [out] Computed Rotation Matrix
    /// @param translation [out] Computed translation Matrix
    void UpdateSpatialMatrix(const BoundingBox& bounding_box,
                             const std::int32_t rows,
                             const std::int32_t cols,
                             cv::Mat& rotational,
                             cv::Mat& translation) const;

    /// @brief Generator for ObjectMessage POD for given Bounding Box and Label. Additional Object properties will be
    /// computed as well suchas distance, position, pose, etc.
    ///
    /// @param bounding_box [in] Object Bounding Box (Result of object detection)
    /// @param label_id [in] Label Id
    ///
    /// @return ObjectMessage (object) information
    ObjectMessage GenerateObjectMessage(const BoundingBox& bounding_box, const LabelId& label_id);

    /// @brief Inference Engine related parametes (i.e. model path, model i/o etc.)
    const InferenceEngineParameters inference_engine_params_;

    /// @brief Instance of Inference Engine (Default: TensorFlowInferenceEngine)
    InferenceEngineStrategy inference_engine_;

    /// @brief Received Camera Image message
    CameraMessage camera_message_;

    /// @brief Received Vehicle velocity
    units::velocity::meters_per_second_t ego_velocity_;

    /// @brief Calculated Objects (List)
    ObjectListMessage object_list_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_OBJECT_H
