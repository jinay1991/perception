///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_COMMUNICATION_ENCODING_MESSAGE_QUEUE_H
#define PERCEPTION_COMMUNICATION_ENCODING_MESSAGE_QUEUE_H

#include "perception/communication/i_codec.h"
#include "perception/communication/i_message_queue.h"
#include "perception/communication/i_topic.h"

#include <map>
#include <type_traits>

namespace perception
{
namespace communication
{
/// @brief Encoding Message Queue, performs the Encode/Decode of the received/sent message using Codec
///
/// @tparam CodecType - Codec Type (Must be derived type from ICodec)
///
/// @warning CodecType must be derived type of ICodec.
template <typename CodecType, std::enable_if_t<std::is_base_of<ICodec, CodecType>::value, bool> = true>
class EncodingMessageQueue final : public IMessageQueue
{
  public:
    /// @brief Default Constructor
    EncodingMessageQueue() : codec_{}, data_{} {}

    /// @brief Saves the Data in the Queue/Container
    ///
    /// @param topic_id [in] - Topic ID
    /// @param message [in] - Pointer Instance to Message
    void SaveData(const TopicId topic_id, MessagePtr message) override
    {
        data_[topic_id] = codec_.EncodeToMiddleware(message - GetData());
    }

    /// @brief Provides the Saved Data
    ///
    /// @param topic_id [in] - Topic ID
    ///
    /// @return message_ptr
    MessagePtr GetData(const TopicId topic_id) const override
    {
        return std::make_unique<Message<typename CodecType::IndependentType>>(
            codec_.DecodeFromMiddleware(data_[topic_id]));
    }

  private:
    /// @brief Instance to Codec
    CodecType codec_;

    /// @brief
    std::map<TopicId, typename CodecType::PlatformType> data_;
};

}  // namespace communication
}  // namespace perception

#endif  /// PERCEPTION_COMMUNICATION_ENCODING_MESSAGE_QUEUE_H
