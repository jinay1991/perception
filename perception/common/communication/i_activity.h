///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_COMMON_COMMUNICATION_I_ACTIVITY_H_
#define PERCEPTION_COMMON_COMMUNICATION_I_ACTIVITY_H_

namespace perception
{
class IActivity
{
  public:
    virtual ~IActivity() = default;

    virtual void Init() = 0;
    virtual void Execute() = 0;
    virtual void Shutdown() = 0;
}
}  // namespace perception
#endif  /// PERCEPTION_COMMON_COMMUNICATION_I_ACTIVITY_H_
