///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/data_source.h"
#include "perception/driver/test/support/builders/driver_camera_message_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{

using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;

constexpr DriverCameraMessage CreateTypicalDriverCameraMessage()
{
    DriverCameraMessage driver_camera_message{};

    driver_camera_message.face_tracking.eye_visibility = true;
    driver_camera_message.face_tracking.eye_lid_opening = 10.0_mm;
    driver_camera_message.face_tracking.eye_blink_rate = 25.0_Hz;

    driver_camera_message.gaze_tracking.pitch = 0.01_rad;
    driver_camera_message.gaze_tracking.roll = 0.01_rad;
    driver_camera_message.gaze_tracking.yaw = 0.01_rad;

    driver_camera_message.head_tracking.pitch = 0.01_rad;
    driver_camera_message.head_tracking.roll = 0.01_rad;
    driver_camera_message.head_tracking.yaw = 0.01_rad;

    return driver_camera_message;
}

class DataSourceTest : public ::testing::Test
{
  public:
    DataSourceTest() : data_source_{} {}

  protected:
    void UpdateDriverCameraMessage(const DriverCameraMessage& driver_camera_message)
    {
        data_source_.UpdateDriverCameraMessage(driver_camera_message);
    }

    const IDataSource& GetDataSource() const { return data_source_; }

  private:
    DataSource data_source_;
};

TEST_F(DataSourceTest, UpdateDriverCameraMessage_GivenTypicalDriverCameraMessage_ExpectUpatedDataSource)
{
    // Given
    const DriverCameraMessage driver_camera_message = DriverCameraMessageBuilder()
                                                          .WithTimePoint(std::chrono::system_clock::now())
                                                          .WithEyeState(true, 10.0_mm, 2.0_Hz)
                                                          .WithHeadPose(0.01_rad, 0.01_rad, 0.01_rad)
                                                          .WithGazePose(0.01_rad, 0.01_rad, 0.01_rad)
                                                          .Build();

    // When
    UpdateDriverCameraMessage(driver_camera_message);

    // Then
    EXPECT_THAT(GetDataSource(),
                AllOf(Property(&IDataSource::GetTimePoint, driver_camera_message.time_point),
                      Property(&IDataSource::IsEyeVisible, driver_camera_message.face_tracking.eye_visibility),
                      Property(&IDataSource::GetEyeLidOpening, driver_camera_message.face_tracking.eye_lid_opening),
                      Property(&IDataSource::GetEyeBlinkRate, driver_camera_message.face_tracking.eye_blink_rate),
                      Property(&IDataSource::GetHeadTracking, driver_camera_message.head_tracking),
                      Property(&IDataSource::GetGazeTracking, driver_camera_message.gaze_tracking)));
}

}  // namespace
}  // namespace perception
