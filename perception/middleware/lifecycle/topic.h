///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_MIDDLEWARE_LIFECYCLE_TOPIC_H_
#define PERCEPTION_MIDDLEWARE_LIFECYCLE_TOPIC_H_

namespace perception
{

template <typename MsgType>
class Topic : public ITopic
{
  public:
    using type = MsgType;

    Topic() = default;
    ~Topic() = default;

    MsgType GetMessage() const { return message_; }
    void SetMessage(const MsgType& message) { message_ = message; }

  protected:
    MsgType message_;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_LIFECYCLE_TOPIC_H_
