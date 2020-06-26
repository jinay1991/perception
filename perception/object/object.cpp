///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

namespace perception
{
Object::Object() : camera_message_{}, object_list_message_{} {}

void Object::Init() {}
void Object::Step() {}
void Object::Shutdown() {}

void Object::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

ObjectListMessage Object::GetObjectListMessage() const
{
    return object_list_message_;
}

}  // namespace perception
