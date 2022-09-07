///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_SUBSCRIBER_H
#define PERCEPTION_COMMUNICATION_I_SUBSCRIBER_H

#include "perception/communication/i_topic.h"

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface for Subscriber
class ISubscriber
{
  public:
    /// @brief Default Destructor
    virtual ~ISubscriber() = default;

    /// @brief Provide Topic ID
    ///
    /// @return topic_id
    virtual TopicId GetTopicId() const = 0;

    /// @brief Updates the Subscriber to receive updated message
    virtual void Update() = 0;
};

/// @brief Pointer Instance of ISubscriber
using SubscriberPtr = std::unique_ptr<ISubscriber>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_SUBSCRIBER_H
