///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_ACTIVITY_DETECTOR_H
#define PERCEPTION_DRIVER_I_ACTIVITY_DETECTOR_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for Activity Detection
class IActivityDetector
{
  public:
    /// @brief Default Destructor
    virtual ~IActivityDetector() = default;

    /// @brief Calculate Driver's Activity based on the received data
    virtual void Step() = 0;

    /// @brief Provides the Activity State, determined based on the received data
    ///
    /// @return state
    virtual ActivityState GetActivityState() const = 0;

    /// @brief Provides the Activity State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    virtual double GetActivityConfidence() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_ACTIVITY_DETECTOR_H
