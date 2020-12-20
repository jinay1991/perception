///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_SENSOR_DRIVER_CAMERA_FACE_DETECT_H
#define PERCEPTION_SENSOR_DRIVER_CAMERA_FACE_DETECT_H

#include "perception/datatypes/camera.h"
#include "perception/sensor/driver_camera/face_detect.h"

namespace perception
{
class FaceDetect
{
  public:
    FaceDetect();

    void Detect(const Image& image);

    const Faces& GetFaces() const;

  private:
    void IdentifyFaces(const Image& image);

    Faces face_list_;
};
}  // namespace perception
#endif  /// PERCEPTION_SENSOR_DRIVER_CAMERA_FACE_DETECT_H
