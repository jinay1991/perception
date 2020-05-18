///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_

#include <cstdint>
#include <memory>

namespace perception
{
using MessageId = std::int32_t;

class IMessage
{
  public:
    virtual ~IMessage() = 0;

    virtual MessageId GetId() const = 0;
};

using MessagePtr = std::unique_ptr<IMessage>;

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_