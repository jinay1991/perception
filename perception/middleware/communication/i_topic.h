///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_TOPIC_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_TOPIC_H_

#include "perception/middleware/communication/i_message.h"

#include <cstdint>

namespace perception
{
using TopicId = std::int32_t;

class ITopic
{
  public:
    virtual ~ITopic() = default;

    virtual TopicId GetId() const = 0;
    virtual MessageId GetMessageId() const = 0;
};

using TopicPtr = std::unique_ptr<ITopic>;

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_TOPICS_H_
