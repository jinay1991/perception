///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_

#include "perception/middleware/communication/i_pub_sub_factory.h"
#include "perception/middleware/communication/publisher_proxy.h"
#include "perception/middleware/communication/subscriber_proxy.h"

namespace perception
{
class IntraProcessPubSubFactory final : public IPubSubFactory
{
  public:
    IntraProcessPubSubFactory() = default;
    ~IntraProcessPubSubFactory() = default;

    void Init() override {}
    void Execute() override {}
    void Shutdown() override {}

    void CreatePublisher(PublisherProxy::PublisherCallback& callback) override {}
    void CreateSubscriber(SubscriberProxy::SubscriberCallback& callback) override {}
};
}  // namespace perception
#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRAPROCESS_PUB_SUB_FACTORY_H_
