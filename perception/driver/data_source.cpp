///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
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

bool DataSource::IsFaceVisible() const
{
    return driver_camera_message_.face_tracking.face_visible;
}

bool DataSource::IsEyeVisible() const
{
    return driver_camera_message_.face_tracking.eye_visible;
}

units::length::millimeter_t DataSource::GetEyeLidOpening() const
{
    return driver_camera_message_.face_tracking.eye_lid_opening;
}

units::frequency::hertz_t DataSource::GetEyeBlinkRate() const
{
    return driver_camera_message_.face_tracking.eye_blink_rate;
}

std::chrono::milliseconds DataSource::GetEyeBlinkDuration() const
{
    const std::chrono::seconds eye_blink_duration{
        static_cast<std::uint32_t>(std::floor(1.0 / GetEyeBlinkRate().value()))};
    return eye_blink_duration;
}

const GazeTracking& DataSource::GetGazeTracking() const
{
    return driver_camera_message_.gaze_tracking;
}

}  // namespace perception
