///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_PARAMETERS_H
#define PERCEPTION_DRIVER_I_PARAMETERS_H

#include <units.h>

namespace perception
{

class IParameters
{
  public:
    virtual ~IParameters() = default;

    virtual bool IsFatigueEnabled() const = 0;
    virtual bool IsVisualAttentionEnabled() const = 0;

    virtual units::length::meter_t GetDistance() const = 0;

    virtual units::angle::radian_t GetYaw() const = 0;
    virtual units::angle::radian_t GetPitch() const = 0;
    virtual units::angle::radian_t GetRoll() const = 0;

    virtual units::length::millimeter_t GetEyeLidOpening() const = 0;
    virtual units::frequency::hertz_t GetEyeBlinkRate() const = 0;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_PARAMETERS_H
