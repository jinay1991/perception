///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_TOPIC_H
#define PERCEPTION_COMMUNICATION_I_TOPIC_H

#include "perception/communication/i_message.h"

#include <cstdint>
#include <memory>

namespace perception
{
namespace communication
{
/// @brief Topic ID
using TopicId = std::int32_t;

/// @brief Interface to Topic
class ITopic
{
  public:
    /// @brief Default Destructor
    virtual ~ITopic() = default;

    /// @brief Provide Topic ID
    ///
    /// @return topic_id
    virtual TopicId GetTopicId() const = 0;

    /// @brief Provide Message ID
    ///
    /// @return message_id
    virtual MessageId GetMessageId() const = 0;
};

/// @brief Pointer Instance to ITopic
using TopicPtr = std::unique_ptr<ITopic>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_TOPIC_H
