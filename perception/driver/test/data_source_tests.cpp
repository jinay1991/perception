///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/data_source.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using namespace units::literals;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;

constexpr DriverCameraSystem CreateTypicalDriverCameraSystem()
{
    DriverCameraSystem driver_camera_system{};

    driver_camera_system.face_tracking.eye_visibility = true;
    driver_camera_system.face_tracking.eye_lid_opening = 10.0_mm;
    driver_camera_system.face_tracking.eye_blink_rate = 25.0_Hz;

    driver_camera_system.gaze_tracking.pitch = 0.01_rad;
    driver_camera_system.gaze_tracking.roll = 0.01_rad;
    driver_camera_system.gaze_tracking.yaw = 0.01_rad;

    driver_camera_system.head_tracking.pitch = 0.01_rad;
    driver_camera_system.head_tracking.roll = 0.01_rad;
    driver_camera_system.head_tracking.yaw = 0.01_rad;

    return driver_camera_system;
}

class DataSourceTest : public ::testing::Test
{
  public:
    DataSourceTest() : data_source_{} {}

  protected:
    void UpdateDriverCameraSystem(const DriverCameraSystem& driver_camera_system)
    {
        data_source_.UpdateDriverCameraSystem(driver_camera_system);
    }

    const IDataSource& GetDataSource() const { return data_source_; }

  private:
    DataSource data_source_;
};

TEST_F(DataSourceTest, UpdateDriverCameraSystem_GivenTypicalDriverCameraSystem_ExpectUpatedDataSource)
{
    // Given
    const DriverCameraSystem driver_camera_system = CreateTypicalDriverCameraSystem();

    // When
    UpdateDriverCameraSystem(driver_camera_system);

    // Then
    EXPECT_THAT(GetDataSource(),
                AllOf(Property(&IDataSource::GetTimePoint, driver_camera_system.time_point),
                      Property(&IDataSource::GetFaceTracking, driver_camera_system.face_tracking),
                      Property(&IDataSource::GetHeadTracking, driver_camera_system.head_tracking),
                      Property(&IDataSource::GetGazeTracking, driver_camera_system.gaze_tracking)));
}

}  // namespace
}  // namespace perception
