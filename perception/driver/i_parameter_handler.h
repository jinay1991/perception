///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H

#include "perception/driver/i_activity_parameter_handler.h"
#include "perception/driver/i_distraction_parameter_handler.h"
#include "perception/driver/i_fatigue_parameter_handler.h"
#include "perception/driver/i_responsiveness_parameter_handler.h"

namespace perception
{
namespace driver
{

/// @brief Parameter handler interface
class IParameterHandler : public IFatigueParameterHandler,
                          public IDistractionParameterHandler,
                          public IActivityParameterHandler,
                          public IResponsivenessParameterHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IParameterHandler() = default;

    /// @brief Provide Minimum Vehicle Velocity Required for System
    ///
    /// @return minimum_velocity
    virtual units::velocity::meters_per_second_t GetMinVelocity() const = 0;

    /// @brief Provide Maximum Vehicle Velocity Required for System
    ///
    /// @return maximum_velocity
    virtual units::velocity::meters_per_second_t GetMaxVelocity() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H
