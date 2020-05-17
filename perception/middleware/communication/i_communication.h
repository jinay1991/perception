///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_I_COMMUNICATION_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_I_COMMUNICATION_H_

namespace perception
{

class ICommunication
{
  public:
    virtual ~ICommunication() = default;

    virtual void Init() = 0;
    virtual void Execute() = 0;
    virtual void Shutdown() = 0;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_I_COMMUNICATION_H_
