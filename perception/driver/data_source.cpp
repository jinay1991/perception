///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/data_source.h"

namespace perception
{
DataSource::DataSource() : driver_camera_message_{} {}

void DataSource::UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
{
    driver_camera_message_ = driver_camera_message;
}

std::chrono::system_clock::time_point DataSource::GetTimePoint() const
{
    return driver_camera_message_.time_point;
}

const HeadTracking& DataSource::GetHeadTracking() const
{
    return driver_camera_message_.head_tracking;
}

bool DataSource::IsEyeVisible() const
{
    return driver_camera_message_.face_tracking.eye_visibility;
}

units::length::millimeter_t DataSource::GetEyeLidOpening() const
{
    return driver_camera_message_.face_tracking.eye_lid_opening;
}

units::frequency::hertz_t DataSource::GetEyeBlinkRate() const
{
    return driver_camera_message_.face_tracking.eye_blink_rate;
}

const GazeTracking& DataSource::GetGazeTracking() const
{
    return driver_camera_message_.gaze_tracking;
}

}  // namespace perception
