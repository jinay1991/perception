///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_TOPICS_H
#define PERCEPTION_COMMUNICATION_TOPICS_H

#include "middleware/communication/topic.h"
#include "perception/datatypes/camera.h"
#include "perception/datatypes/lane.h"
#include "perception/datatypes/object.h"

namespace perception
{

class CameraTopic : public middleware::Topic<CameraMessage>
{
};
class LaneTopic : public middleware::Topic<LaneMessage>
{
};
class ObjectTopic : public middleware::Topic<ObjectMessage>
{
};

}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_TOPICS_H
