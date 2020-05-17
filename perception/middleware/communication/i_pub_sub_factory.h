///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUB_SUB_FACTORY_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_PUB_SUB_FACTORY_H_

namespace perception
{

class IPubSubFactory
{
  public:
    virtual ~IPubSubFactory() = default;

    virtual void Init() = 0;
    virtual void Execute() = 0;
    virtual void Shutdown() = 0;

    virtual void CreatePublisher() = 0;
    virtual void CreateSubscriber() = 0;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_COMMUNICATION_H_
