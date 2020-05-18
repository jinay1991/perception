///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_SUBCRIBER_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_SUBCRIBER_H_

#include <memory>

namespace perception
{
class ISubscriber
{
  public:
    virtual ~ISubscriber() = default;

    virtual void Update() = 0;
};

using SubscriberPtr = std::unique_ptr<ISubscriber>;

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_SUBCRIBER_H_