////
/// @file
/// @brief Contains list of topics and their PODs for intra-process communication (in middleware)
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_BASIC_TOPICS_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_BASIC_TOPICS_H_

#include "perception/datatypes/camera.h"
#include "perception/datatypes/lane.h"
#include "perception/middleware/communication/topic.h"

namespace perception
{
class ImageTopic : public Topic<Image>
{
};

class LaneTopic : public Topic<Lane>
{
};
}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_BASIC_TOPICS_H_
