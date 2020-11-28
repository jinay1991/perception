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

    void UpdateDriverCameraSystem(const DriverCameraSystem& driver_camera_system);

    std::chrono::system_clock::time_point GetTimePoint() const override;
    const HeadTracking& GetHeadTracking() const override;
    const FaceTracking& GetFaceTracking() const override;
    const GazeTracking& GetGazeTracking() const override;

  private:
    DriverCameraSystem driver_camera_system_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_DATA_SOURCE_H
