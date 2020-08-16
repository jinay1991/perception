///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_COMMON_PARAMETERS_H
#define PERCEPTION_DRIVER_COMMON_PARAMETERS_H

#include "perception/driver/common/i_parameters.h"

#include <units.h>

namespace perception
{

class Parameters : public IParameters
{
  public:
    Parameters();
    ~Parameters() = default;

    bool IsFatigueEnabled() const override;
    bool IsVisualAttentionEnabled() const override;

    units::length::meter_t GetDistance() const override;
    units::angle::radian_t GetYaw() const override;
    units::angle::radian_t GetPitch() const override;
    units::angle::radian_t GetRoll() const override;

    units::length::millimeter_t GetEyeLidOpening() const override;
    units::frequency::hertz_t GetEyeBlinkRate() const override;

    void SetIsFatigueEnabled(const bool is_fatigue_enabled);
    void SetIsVisualAttentionEnabled(const bool is_visual_attention_enabled);

    void SetDistance(const units::length::meter_t value);
    void SetYaw(const units::angle::radian_t value);
    void SetPitch(const units::angle::radian_t value);
    void SetRoll(const units::angle::radian_t value);

    void SetEyeLidOpening(const units::length::millimeter_t value);
    void SetEyeBlinkRate(const units::frequency::hertz_t value);

  private:
    bool is_fatigue_enabled_;
    bool is_visual_attention_enabled_;

    units::length::meter_t distance_;
    units::angle::radian_t yaw_;
    units::angle::radian_t pitch_;
    units::angle::radian_t roll_;

    units::length::millimeter_t eye_lid_opening_;
    units::frequency::hertz_t eye_blink_rate_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_COMMON_PARAMETERS_H
