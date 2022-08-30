///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_ACTIVITY_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_ACTIVITY_PARAMETER_HANDLER_H

namespace perception
{
namespace driver
{

/// @brief Activity Parameter handler interface
class IActivityParameterHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IActivityParameterHandler() = default;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_ACTIVITY_PARAMETER_HANDLER_H
