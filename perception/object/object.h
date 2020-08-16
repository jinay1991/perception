///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_OBJECT_OBJECT_H
#define PERCEPTION_OBJECT_OBJECT_H

#include "perception/datatypes/camera.h"
#include "perception/datatypes/object.h"
#include "perception/inference_engine/inference_engine_strategy.h"

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

    virtual void SetCameraMessage(const CameraMessage& camera_message);
    virtual ObjectListMessage GetObjectListMessage() const;

  private:
    void UpdateOutputs();

    const InferenceEngineParameters inference_engine_params_;
    InferenceEngineStrategy inference_engine_;
    CameraMessage camera_message_;
    ObjectListMessage object_list_message_;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_OBJECT_H
