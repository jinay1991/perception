///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_OBJECT_OBJECT_H
#define PERCEPTION_OBJECT_OBJECT_H

#include "perception/datatypes/camera.h"
#include "perception/datatypes/object.h"
#include "perception/inference_engine/inference_engine_strategy.h"

#include <opencv4/opencv2/core.hpp>

#include <string>
#include <vector>

namespace perception
{
class Object final
{
  public:
    Object();

    void Init();
    void Step();
    void Shutdown();

    void SetEgoVelocity(const units::velocity::meters_per_second_t& ego_velocity);
    void SetCameraMessage(const CameraMessage& camera_message);
    const ObjectListMessage& GetObjectListMessage() const;

  private:
    /// @brief Update Outputs (aka Object List)
    void UpdateOutputs();

    /// @brief Computes Rotation and Translation Matrices for given Bounding Box
    ///
    /// @param bounding_box[in] Object Bounding Box (Result of object detection)
    /// @param rows[in] Camera Image Rows
    /// @param cols[in] Camera Image Columns
    /// @param rotational[out] Computed Rotation Matrix
    /// @param translation[out] Computed translation Matrix
    void UpdateSpatialMatrix(const BoundingBox& bounding_box,
                             const std::int32_t rows,
                             const std::int32_t cols,
                             cv::Mat& rotational,
                             cv::Mat& translation) const;

    /// @brief Generator for ObjectMessage POD for given Bounding Box and Label. Additional Object properties will be
    /// computed as well suchas distance, position, pose, etc.
    ///
    /// @param bounding_box[in] Object Bounding Box (Result of object detection)
    /// @param label_id[in] Label Id
    ///
    /// @return ObjectMessage (object) information
    ObjectMessage GenerateObjectMessage(const BoundingBox& bounding_box, const LabelId& label_id);

    const InferenceEngineParameters inference_engine_params_;
    InferenceEngineStrategy inference_engine_;
    CameraMessage camera_message_;
    units::velocity::meters_per_second_t ego_velocity_;
    ObjectListMessage object_list_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_OBJECT_H
