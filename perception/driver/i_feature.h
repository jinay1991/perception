///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_FEATURE_H
#define PERCEPTION_DRIVER_I_FEATURE_H

namespace perception
{
namespace driver
{
/// @brief Interface to the provide support for the specific feature
class IFeature
{
  public:
    /// @brief Default Destrcutor
    virtual ~IFeature() = default;

    /// @brief Calculate feature's output based on the received inputs
    virtual void Step() = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_FEATURE_H
