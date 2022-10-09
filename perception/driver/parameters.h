///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_PARAMETERS_H
#define PERCEPTION_DRIVER_PARAMETERS_H

#include "perception/common/validity_range.h"
#include "perception/driver/datatype/driver.h"

#include <units.h>

namespace perception
{
namespace driver
{

/// @brief Fatigue configuration parameters
struct FatigueParameters
{
    /// @brief Eye Lid Opening Range
    ValidityRange<units::length::millimeter_t> eye_lid_opening_range{kMinEyeLidOpening, kMaxEyeLidOpening};

    /// @brief Eye Blink rate range
    ValidityRange<units::frequency::hertz_t> eye_blink_rate{kMinEyeBlinkRate, kMaxEyeBlinkRate};
};

/// @brief Distraction configuration parameters
struct DistractionParameters
{
};

/// @brief Activity configuration parameters
struct ActivityParameters
{
};

/// @brief Responsiveness configuration parameters
struct ResponsivenessParameters
{
};

/// @brief System configuration parameters
struct SystemParameters
{
    /// @brief Vehicle Velocity Range
    ValidityRange<units::velocity::meters_per_second_t> velocity{kMinVelocity, kMaxVelocity};
};

/// @brief Driver configuration parameters
struct Parameters
{
    /// @brief System Parameters
    SystemParameters system_params;

    /// @brief Fatigue Parameters
    FatigueParameters fatigue_params;

    /// @brief Distraction Parameters
    DistractionParameters distraction_params;

    /// @brief Activity Parameters
    ActivityParameters activity_params;

    /// @brief Responsiveness Parameters
    ResponsivenessParameters responsiveness_params;
};

}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_PARAMETERS_H
