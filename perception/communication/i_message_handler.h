///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_MESSAGE_HANDLER_H
#define PERCEPTION_COMMUNICATION_I_MESSAGE_HANDLER_H

#include "perception/communication/i_message.h"

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface for handling Message (Storage)
class IMessageHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IMessageHandler() = default;

    /// @brief Provide Message ID
    ///
    /// @return message_id
    virtual MessageId GetMessageId() const = 0;

    /// @brief Process Message
    ///
    /// @param message [in] - Message
    virtual void HandleMessage(MessagePtr message) = 0;
};

/// @brief Pointer Instance for IMessageHandler
using MessageHandlerPtr = std::unique_ptr<IMessageHandler>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_MESSAGE_HANDLER_H
