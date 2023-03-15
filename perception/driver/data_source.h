///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_DATA_SOURCE_H
#define PERCEPTION_DRIVER_DATA_SOURCE_H

#include "perception/driver/datatype/driver.h"
#include "perception/driver/i_data_source.h"

namespace perception
{
namespace driver
{
/// @brief Data Storage for Driver Camera Information.
/// @note Implements IDataSource.
class DataSource final : public IDataSource
{
  public:
    /// @brief Default Constructor.
    DataSource();

    /// @brief Update Driver Camera Message
    ///
    /// @param driver_camera_message [in] - Driver Camera Message
    void UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message);

    /// @brief Provide timestamp information from the driver camera information
    ///
    /// @return time_point
    std::chrono::system_clock::time_point GetTimePoint() const override;

    /// @brief Provide Head tracking information from the driver camera information
    ///
    /// @return head_tracking
    const HeadTracking& GetHeadTracking() const override;

    /// @brief Provide Gaze tracking information from the driver camera information
    ///
    /// @return gaze_tracking
    const GazeTracking& GetGazeTracking() const override;

    /// @brief Provide face visibility whether it is visible or not
    ///
    /// @return True if face is visible (in driver camera information), otherwise False.
    bool IsFaceVisible() const override;

    /// @brief Provide eyes visibility whether they are visible or not
    ///
    /// @return True if eyes are visible (in driver camera information), otherwise False.
    bool IsEyeVisible() const override;

    /// @brief Provide driver's eye lid opening from the drive camera information
    ///
    /// @return eye lid opening (mm)
    units::length::millimeter_t GetEyeLidOpening() const override;

    /// @brief Provide driver's eye blink rate from the drive camera information
    ///
    /// @return eye blink rate (Hz)
    units::frequency::hertz_t GetEyeBlinkRate() const override;

    /// @brief Provide driver's eye blink duration from the drive camera information
    /// @note Duration is calculated based on the eye blink rate.
    ///
    /// @return eye blink duration (ms)
    std::chrono::milliseconds GetEyeBlinkDuration() const override;

  private:
    /// @brief Stored copy of Driver Camera Message
    DriverCameraMessage driver_camera_message_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_DATA_SOURCE_H
