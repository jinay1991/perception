///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_MESSAGE_H
#define PERCEPTION_COMMUNICATION_MESSAGE_H

#include "perception/communication/i_message.h"

#include <type_traits>

namespace perception
{
namespace communication
{
namespace
{
/// @brief Create Unique Message ID
///
/// @return message_id
static MessageId CreateMessageId() noexcept
{
    static MessageId id{0};
    return ++id;
}
}  // namespace

/// @brief Implementation of Interface IMessage
template <typename IndependentType_, std::enable_if_t<std::is_pod<IndependentType_>::value, bool> = true>
class Message final : public IMessage
{
  public:
    /// @brief Alias to IndependentType
    using IndependentType = IndependentType_;

    /// @brief Default Constructor
    ///
    /// @param data [in] - Message Payload of IndependentType
    explicit Message(const IndependentType& data) : data_{data} {}

    /// @brief Provides Message ID
    ///
    /// @return message_id
    MessageId GetMessageId() const override { return Message<IndependentType>::GetId(); }

    /// @brief Provides Message Payload Data
    ///
    /// @return data
    const IndependentType& GetData() const { return data_; }

  private:
    /// @brief Provides unique ID.
    ///
    /// @note Unique ID is generated and assigned during the construction, due to static nature, and remains same for
    /// provided Message.
    ///
    /// @return message_id
    static MessageId GetId()
    {
        static const MessageId id{CreateMessageId()};
        return id;
    }

    /// @brief Instance to Message Payload Data
    const IndependentType& data_;
};

template <typename IndependentType>
constexpr MessagePtr CreateMessage(const IndependentType& data) noexcept
{
    return std::make_unique<Message<IndependentType>>(data);
}

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_MESSAGE_H
