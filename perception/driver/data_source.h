///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_DATA_SOURCE_H
#define PERCEPTION_DRIVER_DATA_SOURCE_H

#include "perception/datatypes/driver.h"
#include "perception/driver/i_data_source.h"

namespace perception
{

class DataSource : public IDataSource
{
  public:
    DataSource();

    void UpdateDriverCameraSystemMessage(const DriverCameraSystemMessage& driver_camera_system_message);

    std::chrono::system_clock::time_point GetTimePoint() const override;
    const HeadTracking& GetHeadTracking() const override;
    const GazeTracking& GetGazeTracking() const override;

    bool IsEyeVisible() const override;
    units::length::millimeter_t GetEyeLidOpening() const override;
    units::frequency::hertz_t GetEyeBlinkRate() const override;

  private:
    DriverCameraSystemMessage driver_camera_system_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_DATA_SOURCE_H
