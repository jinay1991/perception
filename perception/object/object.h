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
class Object
{
  public:
    Object();
    ~Object() = default;

    virtual void Init();
    virtual void Step();
    virtual void Shutdown();

    virtual void SetEgoVelocity(const units::velocity::meters_per_second_t& ego_velocity);
    virtual void SetCameraMessage(const CameraMessage& camera_message);
    virtual ObjectListMessage GetObjectListMessage() const;

  private:
    void UpdateOutputs();
    void UpdateSpatialMatrix(const BoundingBox& bounding_box,
                             const std::int32_t rows,
                             const std::int32_t cols,
                             cv::Mat& rotational,
                             cv::Mat& translation) const;

    ObjectMessage GenerateObjectMessage(const BoundingBox& bounding_box, const LabelId& label_id);

    const InferenceEngineParameters inference_engine_params_;
    InferenceEngineStrategy inference_engine_;
    CameraMessage camera_message_;
    units::velocity::meters_per_second_t ego_velocity_;
    ObjectListMessage object_list_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_OBJECT_H
