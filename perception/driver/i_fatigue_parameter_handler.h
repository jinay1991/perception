///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_FATIGUE_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_FATIGUE_PARAMETER_HANDLER_H

#include <units.h>

namespace perception
{
namespace driver
{

/// @brief Fatigue Parameter handler interface
class IFatigueParameterHandler
{
  public:
    /// @brief Default Destructor
    virtual ~IFatigueParameterHandler() = default;

    /// @brief Provide set maximum eye lid opening
    ///
    /// @return max_eye_lid_opening (mm)
    virtual units::length::millimeter_t GetMaxEyeLidOpening() const = 0;

    /// @brief Provide set minimum eye lid opening
    ///
    /// @return min_eye_lid_opening (mm)
    virtual units::length::millimeter_t GetMinEyeLidOpening() const = 0;

    /// @brief Provide set maximum eye blink rate
    ///
    /// @return max_eye_blink_rate (hertz)
    virtual units::frequency::hertz_t GetMinEyeBlinkRate() const = 0;

    /// @brief Provide set minimum eye blink rate
    ///
    /// @return min_eye_blink_rate (hertz)
    virtual units::frequency::hertz_t GetMaxEyeBlinkRate() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_FATIGUE_PARAMETER_HANDLER_H
