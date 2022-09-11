///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_RESPONSIVENESS_DETECTOR_H
#define PERCEPTION_DRIVER_I_RESPONSIVENESS_DETECTOR_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{
/// @brief Interface class for Responsiveness Detection
class IResponsivenessDetector
{
  public:
    /// @brief Default Destructor
    virtual ~IResponsivenessDetector() = default;

    /// @brief Calculate Driver's Responsiveness based on the received data
    virtual void Step() = 0;

    /// @brief Provides the Responsiveness State, determined based on the received data
    ///
    /// @return Responsiveness_state
    virtual ResponsivenessState GetResponsivenessState() const = 0;

    /// @brief Provides the Responsiveness State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    virtual double GetResponsivenessConfidence() const = 0;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_RESPONSIVENESS_DETECTOR_H
