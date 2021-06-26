///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_I_DATA_SOURCE_H
#define PERCEPTION_DRIVER_I_DATA_SOURCE_H

#include "perception/datatypes/driver.h"

namespace perception
{
/// @brief Interface class for storing and providing interfaces to access received information (Driver Camera
/// Information)
class IDataSource
{
  public:
    /// @brief Default Destructor
    virtual ~IDataSource() = default;

    /// @brief Interface to obtain timestamp information from the driver camera information
    ///
    /// @return time_point
    virtual std::chrono::system_clock::time_point GetTimePoint() const = 0;

    /// @brief Interface to obtain Head tracking information from the driver camera information
    ///
    /// @return head_tracking
    virtual const HeadTracking& GetHeadTracking() const = 0;

    /// @brief Interface to obtain Gaze Tracking information from the driver camera information
    ///
    /// @return gaze_tracking
    virtual const GazeTracking& GetGazeTracking() const = 0;

    /// @brief Interface to obtain whether face is visible or not
    ///
    /// @return True if face is visible (in driver camera information), otherwise False.
    virtual bool IsFaceVisible() const = 0;

    /// @brief Interface to obtain whether eyes are visible or not
    ///
    /// @return True if eyes are visible (in driver camera information), otherwise False.
    virtual bool IsEyeVisible() const = 0;

    /// @brief Interface to obtain driver's eye lid opening from the drive camera information
    ///
    /// @return eye lid opening (mm)
    virtual units::length::millimeter_t GetEyeLidOpening() const = 0;

    /// @brief Interface to obtain driver's eye blink rate from the drive camera information
    ///
    /// @return eye blink rate (Hz)
    virtual units::frequency::hertz_t GetEyeBlinkRate() const = 0;

    /// @brief Interface to obtain driver's eye blink duration from the drive camera information
    /// @note Duration is calculated based on the eye blink rate.
    ///
    /// @return eye blink duration (ms)
    virtual std::chrono::milliseconds GetEyeBlinkDuration() const = 0;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_I_DATA_SOURCE_H
