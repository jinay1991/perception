///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_RESPONSIVENESS_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_RESPONSIVENESS_PARAMETER_HANDLER_H

namespace perception
{
namespace driver
{

/// @brief Fatigue Parameter handler interface
class IResponsivenessParameterHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IResponsivenessParameterHandler() = default;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_RESPONSIVENESS_PARAMETER_HANDLER_H
