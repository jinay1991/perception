///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_

#include "perception/middleware/communication/i_message.h"

#include <memory>

namespace perception
{

template <typename IndependentType>
class Message : public IMessage
{
  public:
    explicit Message(const IndependentType& data) : data_{data} {}

    ~Message() = default;

    virtual MessageId GetId() const override { return 0; };

  private:
    IndependentType data_;
};

template <typename IndependentType>
MessagePtr CreateMessage(const IndependentType& data)
{
    return std::make_unique<Message<IndependentType>>(data);
}
}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_MESSAGE_H_