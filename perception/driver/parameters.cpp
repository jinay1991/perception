///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/common/parameters.h"

namespace perception
{
Parameters::Parameters()
    : is_fatigue_enabled_{false},
      is_visual_attention_enabled_{false},
      distance_{0.0},
      yaw_{0.0},
      pitch_{0.0},
      roll_{0.0},
      eye_lid_opening_{0.0},
      eye_blink_rate_{0.0}
{
}

bool Parameters::IsFatigueEnabled() const
{
    return is_fatigue_enabled_;
}

bool Parameters::IsVisualAttentionEnabled() const
{
    return is_visual_attention_enabled_;
}

units::length::meter_t Parameters::GetDistance() const
{
    return distance_;
}

units::angle::radian_t Parameters::GetYaw() const
{
    return yaw_;
}

units::angle::radian_t Parameters::GetPitch() const
{
    return pitch_;
}

units::angle::radian_t Parameters::GetRoll() const
{
    return roll_;
}

units::length::millimeter_t Parameters::GetEyeLidOpening() const
{
    return eye_lid_opening_;
}
units::frequency::hertz_t Parameters::GetEyeBlinkRate() const
{
    return eye_blink_rate_;
}

void Parameters::SetIsFatigueEnabled(const bool is_fatigue_enabled)
{
    is_fatigue_enabled_ = is_fatigue_enabled;
}

void Parameters::SetIsVisualAttentionEnabled(const bool is_visual_attention_enabled)
{
    is_visual_attention_enabled_ = is_visual_attention_enabled;
}

void Parameters::SetDistance(const units::length::meter_t distance)
{
    distance_ = distance;
}

void Parameters::SetYaw(const units::angle::radian_t yaw)
{
    yaw_ = yaw;
}

void Parameters::SetPitch(const units::angle::radian_t pitch)
{
    pitch_ = pitch;
}

void Parameters::SetRoll(const units::angle::radian_t roll)
{
    roll_ = roll;
}

void Parameters::SetEyeLidOpening(const units::length::millimeter_t eye_lid_opening)
{
    eye_lid_opening_ = eye_lid_opening;
}

void Parameters::SetEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate)
{
    eye_blink_rate_ = eye_blink_rate;
}
}  // namespace perception
