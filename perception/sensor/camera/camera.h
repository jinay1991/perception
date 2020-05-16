///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_SENSOR_CAMERA_CAMERA_H_
#define PERCEPTION_SENSOR_CAMERA_CAMERA_H_

#include "perception/datatypes/image.h"

namespace perception
{
class Camera
{
  public:
    Camera();

    virtual void Init();
    virtual void Execute();
    virtual void Shutdown();

    Image GetImage() const;

  private:
    Image image_;
};
}  // namespace perception

#endif  /// PERCEPTION_SENSOR_CAMERA_CAMERA_H_
