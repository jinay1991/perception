///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_FATIGUE_DETECTOR_H
#define PERCEPTION_DRIVER_I_FATIGUE_DETECTOR_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for Fatigue Detection
class IFatigueDetector
{
  public:
    /// @brief Default Destructor
    virtual ~IFatigueDetector() = default;

    /// @brief Calculate Driver's Fatigue based on the received data
    virtual void Step() = 0;

    /// @brief Provides the Fatigue State, determined based on the received data
    ///
    /// @return fatigue_state
    virtual FatigueState GetFatigueState() const = 0;

    /// @brief Provides the Fatigue State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    virtual double GetFatigueConfidence() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_FATIGUE_DETECTOR_H
