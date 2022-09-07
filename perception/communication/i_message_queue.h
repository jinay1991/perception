///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_MESSAGE_QUEUE_H
#define PERCEPTION_COMMUNICATION_I_MESSAGE_QUEUE_H

#include "perception/communication/i_message.h"
#include "perception/communication/i_topic.h"

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface to Message Queue.
class IMessageQueue
{
  public:
    /// @brief Default Destructor
    virtual ~IMessageQueue() = default;

    /// @brief Saves the Data in the Queue/Container
    ///
    /// @param topic_id [in] - Topic ID
    /// @param message [in] - Pointer Instance to Message
    virtual void SaveData(const TopicId topic_id, MessagePtr message) = 0;

    /// @brief Provides the Saved Data
    ///
    /// @param topic_id [in] - Topic ID
    ///
    /// @return message
    virtual MessagePtr GetData(const TopicId topic_id) const = 0;
};

/// @brief Pointer Instance to IMessageQueue
using MessageQueuePtr = std::unique_ptr<IMessageQueue>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_MESSAGE_QUEUE_H
