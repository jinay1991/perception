///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/parameter_handler.h"

namespace perception
{
namespace driver
{

ParameterHandler::ParameterHandler() : parameters_{} {}

units::length::millimeter_t ParameterHandler::GetMaxEyeLidOpening() const
{
    return parameters_.fatigue_params.eye_lid_opening_range.upper;
}

units::length::millimeter_t ParameterHandler::GetMinEyeLidOpening() const
{
    return parameters_.fatigue_params.eye_lid_opening_range.lower;
}

units::frequency::hertz_t ParameterHandler::GetMinEyeBlinkRate() const
{
    return parameters_.fatigue_params.eye_blink_rate.lower;
}

units::frequency::hertz_t ParameterHandler::GetMaxEyeBlinkRate() const
{
    return parameters_.fatigue_params.eye_blink_rate.upper;
}

units::velocity::meters_per_second_t ParameterHandler::GetMinVelocity() const
{
    return parameters_.system_params.velocity.lower;
}

units::velocity::meters_per_second_t ParameterHandler::GetMaxVelocity() const
{
    return parameters_.system_params.velocity.upper;
}

void ParameterHandler::SetMinEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.fatigue_params.eye_lid_opening_range.lower = eye_lid_opening;
}

void ParameterHandler::SetMaxEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    parameters_.fatigue_params.eye_lid_opening_range.upper = eye_lid_opening;
}

void ParameterHandler::SetMinEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    parameters_.fatigue_params.eye_blink_rate.lower = eye_blink_rate;
}

void ParameterHandler::SetMaxEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    parameters_.fatigue_params.eye_blink_rate.upper = eye_blink_rate;
}

void ParameterHandler::SetMinVelocity(const units::velocity::meters_per_second_t velocity)
{
    parameters_.system_params.velocity.lower = velocity;
}

void ParameterHandler::SetMaxVelocity(const units::velocity::meters_per_second_t velocity)
{
    parameters_.system_params.velocity.upper = velocity;
}
}  // namespace driver
}  // namespace perception
