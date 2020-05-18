///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_

#include "perception/middleware/communication/i_message.h"
#include "perception/middleware/communication/i_pub_sub_factory.h"
#include "perception/middleware/communication/i_publisher.h"
#include "perception/middleware/communication/i_subscriber.h"

namespace perception
{

class IntraProcessPubSubFactory final : public IPubSubFactory
{
  public:
    IntraProcessPubSubFactory() = default;
    ~IntraProcessPubSubFactory() = default;

    void Update();

    PublisherPtr CreatePublisher(const TopicId topic, const MessagePtr message) override;
    SubscriberPtr CreateSubscriber(const TopicId topic, const MessagePtr message) override;
};
}  // namespace perception
#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_
