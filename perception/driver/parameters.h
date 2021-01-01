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

struct Parameters
{
    ValidityRange<units::length::millimeter_t> eye_lid_opening_range{kMinEyeLidOpening, kMaxEyeLidOpening};
    ValidityRange<units::frequency::hertz_t> eye_blink_rate{kMinEyeBlinkRate, kMaxEyeBlinkRate};
};

}  // namespace perception
#endif  /// PERCEPTION_DRIVER_PARAMETERS_H
