///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUBLISHER_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUBLISHER_H_

#include "perception/middleware/communication/i_message.h"

#include <memory>

namespace perception
{
class IPublisher
{
  public:
    virtual ~IPublisher() = default;

    virtual void Publish(const std::unique_ptr<IMessage>& message) = 0;
};

using PublisherPtr = std::unique_ptr<IPublisher>;

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUBLISHER_H_