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
using ::testing::Property;

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

    static std::chrono::milliseconds CalculateDuration(const units::frequency::hertz_t rate)
    {

        const std::chrono::seconds duration{static_cast<std::int32_t>(std::floor(1.0 / rate.value()))};
        return duration;
    }

  private:
    DataSource data_source_;
};

TEST_F(DataSourceTest, UpdateDriverCameraMessage_GivenTypicalDriverCameraMessage_ExpectUpdatedDataSource)
{
    // Given
    const DriverCameraMessage& driver_camera_message = DriverCameraMessageBuilder()
                                                           .WithTimePoint(std::chrono::system_clock::now())
                                                           .WithEyeState(true, true, 10.0_mm, 2.0_Hz)
                                                           .WithHeadPose(0.01_rad, 0.01_rad, 0.01_rad)
                                                           .WithGazePose(0.01_rad, 0.01_rad, 0.01_rad)
                                                           .Build();

    // When
    UpdateDriverCameraMessage(driver_camera_message);

    // Then
    EXPECT_THAT(GetDataSource(),
                AllOf(Property(&IDataSource::GetTimePoint, driver_camera_message.time_point),
                      Property(&IDataSource::IsFaceVisible, driver_camera_message.face_tracking.face_visibility),
                      Property(&IDataSource::IsEyeVisible, driver_camera_message.face_tracking.eye_visibility),
                      Property(&IDataSource::GetEyeLidOpening, driver_camera_message.face_tracking.eye_lid_opening),
                      Property(&IDataSource::GetEyeBlinkRate, driver_camera_message.face_tracking.eye_blink_rate),
                      Property(&IDataSource::GetEyeBlinkDuration,
                               CalculateDuration(driver_camera_message.face_tracking.eye_blink_rate)),
                      Property(&IDataSource::GetHeadTracking, driver_camera_message.head_tracking),
                      Property(&IDataSource::GetGazeTracking, driver_camera_message.gaze_tracking)));
}

}  // namespace
}  // namespace perception
