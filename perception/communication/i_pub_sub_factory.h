///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_I_PUB_SUB_FACTORY_H
#define PERCEPTION_COMMUNICATION_I_PUB_SUB_FACTORY_H

#include "perception/communication/i_message_handler.h"
#include "perception/communication/i_topic.h"

#include <memory>

namespace perception
{
namespace communication
{
/// @brief Interface to Publisher Subscriber Factory.
class IPubSubFactory
{
  public:
    /// @brief Default Destructor
    virtual ~IPubSubFactory() = default;

    /// @brief Creates Subscriber for provided Topic ID
    ///
    /// @param topic_id [in] - Topic ID
    virtual void CreateSubscriber(const TopicId topic_id) = 0;

    /// @brief Creates Publisher for provided Topic ID
    ///
    /// @param topic_id [in] - Topic ID
    /// @param handler [in] - Pointer to Message Handler
    virtual void CreatePublisher(const TopicId topic_id, const MessageHandlerPtr handler) = 0;
};

/// @brief Pointer Instance of IPubSubFactory
using PubSubFactoryPtr = std::unique_ptr<IPubSubFactory>;

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_I_PUB_SUB_FACTORY_H
