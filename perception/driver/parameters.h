///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_PARAMETERS_H
#define PERCEPTION_DRIVER_PARAMETERS_H

#include "perception/common/validity_range.h"
#include "perception/datatypes/driver.h"

namespace perception
{

/// @brief Driver configuration parameters
struct Parameters
{
    /// @brief Eye Lid Opening Range
    ValidityRange<units::length::millimeter_t> eye_lid_opening_range{kMinEyeLidOpening, kMaxEyeLidOpening};

    /// @brief Eye Blink rate range
    ValidityRange<units::frequency::hertz_t> eye_blink_rate{kMinEyeBlinkRate, kMaxEyeBlinkRate};
};

}  // namespace perception
#endif  /// PERCEPTION_DRIVER_PARAMETERS_H
