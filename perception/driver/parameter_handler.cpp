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

units::frequency::hertz_t ParameterHandler::GetMinEyeBlinkRate() const
{
    return parameters_.eye_blink_rate.lower;
}

units::frequency::hertz_t ParameterHandler::GetMaxEyeBlinkRate() const
{
    return parameters_.eye_blink_rate.upper;
}

void ParameterHandler::SetMinEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.eye_lid_opening_range.lower = eye_lid_opening;
}

void ParameterHandler::SetMaxEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.eye_lid_opening_range.upper = eye_lid_opening;
}

void ParameterHandler::SetMinEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    parameters_.eye_blink_rate.lower = eye_blink_rate;
}

void ParameterHandler::SetMaxEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    parameters_.eye_blink_rate.upper = eye_blink_rate;
}
}  // namespace perception
