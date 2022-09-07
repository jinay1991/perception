///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_MESSAGE_H
#define PERCEPTION_COMMUNICATION_I_MESSAGE_H

#include <cstdint>
#include <memory>

namespace perception
{
namespace communication
{

/// @brief Message ID
using MessageId = std::int32_t;

/// @brief Interface of Message Type
class IMessage
{
  public:
    /// @brief Default Destructor
    virtual ~IMessage() = default;

    /// @brief Provides Message ID
    ///
    /// @return message_id
    virtual MessageId GetMessageId() const = 0;
};

/// @brief Pointer Instance to IMessage
using MessagePtr = std::unique_ptr<IMessage>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_MESSAGE_H
