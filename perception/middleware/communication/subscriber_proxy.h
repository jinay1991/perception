///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_SUBSCRIBER_PROXY_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_SUBSCRIBER_PROXY_H_

#include "perception/middleware/communication/i_communication.h"

namespace perception
{

template <typename MsgType>
class SubscriberProxy : public ICommunication
{
  public:
    SubscriberProxy() = default;
    ~SubscriberProxy() = default;

    void Init() override {}
    void Execute() override {}
    void Shutdown() override {}
};
}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_SUBSCRIBER_PROXY_H_
