///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUB_SUB_FACTORY_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUB_SUB_FACTORY_H_

#include "perception/middleware/communication/i_publisher.h"
#include "perception/middleware/communication/i_subscriber.h"

#include <memory>

namespace perception
{
using TopicId = std::int32_t;

class IPubSubFactory
{
  public:
    virtual ~IPubSubFactory() = default;

    virtual PublisherPtr CreatePublisher(const TopicId topic, const MessagePtr message) = 0;
    virtual SubscriberPtr CreateSubscriber(const TopicId topic, const MessagePtr message) = 0;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_COMMUNICATION_H_
