///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/data_source.h"

namespace perception
{
DataSource::DataSource() {}

void DataSource::UpdateDriverCameraSystem(const DriverCameraSystem& driver_camera_system)
{
    driver_camera_system_ = driver_camera_system;
}

std::chrono::system_clock::time_point DataSource::GetTimePoint() const
{
    return driver_camera_system_.time_point;
}

const HeadTracking& DataSource::GetHeadTracking() const
{
    return driver_camera_system_.head_tracking;
}

const FaceTracking& DataSource::GetFaceTracking() const
{
    return driver_camera_system_.face_tracking;
}

const GazeTracking& DataSource::GetGazeTracking() const
{
    return driver_camera_system_.gaze_tracking;
}
}  // namespace perception
