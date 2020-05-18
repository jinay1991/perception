///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_TOPIC_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_TOPIC_H_

#include "perception/middleware/communication/i_message.h"
#include "perception/middleware/communication/i_topic.h"
#include "perception/middleware/communication/message.h"

#include <functional>

namespace perception
{

template <typename IndependentType>
class Topic : public ITopic
{
  public:
    using MessageType = IndependentType;

    using SubscriberCallback = std::function<void(const MessageType&)>;
    using PublisherCallback = std::function<MessageType(void)>;

    Topic() = default;
    ~Topic() = default;

    TopicId GetId() const override { return Id(); }
    MessageId GetMessageId() const override { return Message<IndependentType>::Id(); }

  private:
    TopicId Id() { return 0; }
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_TOPIC_H_
