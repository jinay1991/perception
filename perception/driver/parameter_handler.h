///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_PARAMETER_HANDLER_H

#include "perception/driver/i_parameter_handler.h"
#include "perception/driver/parameters.h"

namespace perception
{

class ParameterHandler final : public IParameterHandler
{
  public:
    ParameterHandler();

    units::length::millimeter_t GetMaxEyeLidOpening() const override;
    units::length::millimeter_t GetMinEyeLidOpening() const override;

    units::frequency::hertz_t GetMinEyeBlinkRate() const override;
    units::frequency::hertz_t GetMaxEyeBlinkRate() const override;

    void SetMinEyeLidOpening(const units::length::millimeter_t eye_lid_opening);
    void SetMaxEyeLidOpening(const units::length::millimeter_t eye_lid_opening);

    void SetMinEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate);
    void SetMaxEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate);

  private:
    Parameters parameters_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_PARAMETER_HANDLER_H
