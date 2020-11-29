///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/parameter_handler.h"

namespace perception
{

ParameterHandler::ParameterHandler() : parameters_{} {}

units::length::millimeter_t ParameterHandler::GetMaxEyeLidOpening() const
{
    return parameters_.eye_lid_opening_range.upper;
}

units::length::millimeter_t ParameterHandler::GetMinEyeLidOpening() const
{
    return parameters_.eye_lid_opening_range.lower;
}

units::frequency::hertz_t ParameterHandler::GetEyeBlinkRate() const
{
    return parameters_.eye_blink_rate;
}

void ParameterHandler::SetMinEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.eye_lid_opening_range.lower = eye_lid_opening;
}

void ParameterHandler::SetMaxEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.eye_lid_opening_range.upper = eye_lid_opening;
}

void ParameterHandler::SetEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    parameters_.eye_blink_rate = eye_blink_rate;
}
}  // namespace perception
