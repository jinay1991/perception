///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_TOPICS_H
#define PERCEPTION_COMMUNICATION_TOPICS_H

#include "middleware/communication/topic.h"
#include "perception/datatypes/camera.h"

namespace perception
{

class CameraTopic : public middleware::Topic<CameraMessage>
{
};

}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_TOPICS_H
