///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_PARAMETER_HANDLER_H
#define PERCEPTION_DRIVER_PARAMETER_HANDLER_H

#include "perception/driver/i_parameter_handler.h"
#include "perception/driver/parameters.h"

namespace perception
{

/// @brief Parameter handler
class ParameterHandler final : public IParameterHandler
{
  public:
    /// @brief Default constructor.
    ParameterHandler();

    /// @brief Provide set maximum eye lid opening
    ///
    /// @return max_eye_lid_opening (mm)
    units::length::millimeter_t GetMaxEyeLidOpening() const override;

    /// @brief Provide set minimum eye lid opening
    ///
    /// @return min_eye_lid_opening (mm)
    units::length::millimeter_t GetMinEyeLidOpening() const override;

    /// @brief Provide set maximum eye blink rate
    ///
    /// @return max_eye_blink_rate (hertz)
    units::frequency::hertz_t GetMinEyeBlinkRate() const override;

    /// @brief Provide set minimum eye blink rate
    ///
    /// @return min_eye_blink_rate (hertz)
    units::frequency::hertz_t GetMaxEyeBlinkRate() const override;

    /// @brief Set minimum eye lid opening
    ///
    /// @param eye_lid_opening [in] - Eye Lid Opening (mm)
    void SetMinEyeLidOpening(const units::length::millimeter_t eye_lid_opening);

    /// @brief Set maximum eye lid opening
    ///
    /// @param eye_lid_opening [in] - Eye Lid Opening (mm)
    void SetMaxEyeLidOpening(const units::length::millimeter_t eye_lid_opening);

    /// @brief Set minimum eye blink rate
    ///
    /// @param eye_blink_rate [in] - Eye Blink Rate (hertz)
    void SetMinEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate);

    /// @brief Set maximum eye blink rate
    ///
    /// @param eye_blink_rate [in] - Eye Blink Rate (hertz)
    void SetMaxEyeBlinkRate(const units::frequency::hertz_t eye_blink_rate);

  private:
    /// @brief Parameter
    Parameters parameters_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_PARAMETER_HANDLER_H
