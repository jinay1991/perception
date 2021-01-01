///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H

#include <units.h>

#include <chrono>

namespace perception
{

class IParameterHandler
{
  public:
    virtual ~IParameterHandler() = default;

    virtual units::length::millimeter_t GetMaxEyeLidOpening() const = 0;
    virtual units::length::millimeter_t GetMinEyeLidOpening() const = 0;
    virtual units::frequency::hertz_t GetMinEyeBlinkRate() const = 0;
    virtual units::frequency::hertz_t GetMaxEyeBlinkRate() const = 0;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_PARAMETER_HANDLER_H
