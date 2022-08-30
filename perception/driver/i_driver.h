///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DRIVER_H
#define PERCEPTION_DRIVER_I_DRIVER_H

#include "perception/driver/datatype/driver.h"

namespace perception
{
namespace driver
{

/// @brief Interface to Driver Model (Driver Monitoring)
class IDriver
{
  public:
    /// @brief Default Destructor
    virtual ~IDriver() = default;

    /// @brief Process received input (driver camera message)
    ///
    /// @param driver_camera_message [in] - Driver Camera Message
    virtual void UpdateDriverCameraMessage(const DriverCameraMessage& message) = 0;

    /// @brief Evaluate Driver's Fatigue, Visual Distraction, Activity and Responsiveness
    virtual void Step() = 0;

    /// @brief Provide (monitored) Driver's State Information
    ///
    /// @return driver_message
    virtual const DriverMessage& GetDriverMessage() const = 0;
};
}  // namespace driver
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_I_DRIVER_H
