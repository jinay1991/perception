///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_PUBLISHER_H
#define PERCEPTION_COMMUNICATION_I_PUBLISHER_H

#include "perception/communication/i_message.h"
#include "perception/communication/i_topic.h"

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface for Publisher
class IPublisher
{
  public:
    /// @brief Default Destructor
    virtual ~IPublisher() = default;

    /// @brief Provide Topic ID
    ///
    /// @return topic_id
    virtual TopicId GetTopicId() const = 0;

    /// @brief Publishes provided Message
    ///
    /// @param message [in] - Pointer Instance of Message
    virtual void Publish(MessagePtr message) = 0;
};

/// @brief Pointer Instance of IPublisher
using PublisherPtr = std::unique_ptr<IPublisher>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_PUBLISHER_H
