///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DISTRACTION_DETECTOR_H
#define PERCEPTION_DRIVER_I_DISTRACTION_DETECTOR_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for Distraction Detection
class IDistractionDetector
{
  public:
    /// @brief Default Destructor
    virtual ~IDistractionDetector() = default;

    /// @brief Calculate Driver's Distraction based on the received data
    virtual void Step() = 0;

    /// @brief Provides the Distraction State, determined based on the received data
    ///
    /// @return state
    virtual DistractionState GetDistractionState() const = 0;

    /// @brief Provides the Distraction State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    virtual double GetDistractionConfidence() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_DISTRACTION_DETECTOR_H
