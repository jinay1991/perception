///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DATATYPES_TEST_CAMERA_MESSAGE_BUILDER_H
#define PERCEPTION_DATATYPES_TEST_CAMERA_MESSAGE_BUILDER_H

#include "perception/datatypes/camera.h"

namespace perception
{
namespace
{
class CameraMessageBuilder
{
  public:
    CameraMessageBuilder() : camera_message_{} {}
    ~CameraMessageBuilder() = default;

    CameraMessageBuilder& WithImage() { return *this; }

    CameraMessage Build() const { return camera_message_; }

  private:
    CameraMessage camera_message_;
};
}  // namespace
}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_TEST_CAMERA_MESSAGE_BUILDER_H