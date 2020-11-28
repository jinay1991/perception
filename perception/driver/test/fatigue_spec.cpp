///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"
#include "perception/driver/parameters.h"
#include "perception/driver/test/support/driver_camera_system_builder.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

namespace perception
{
namespace
{
using ::testing::Field;
using ::testing::Return;
using ::testing::ReturnRef;
using namespace units::literals;

class DataSourceMock : public IDataSource
{
  public:
    DataSourceMock() = default;

    MOCK_CONST_METHOD0(GetTimePoint, std::chrono::system_clock::time_point());
    MOCK_CONST_METHOD0(GetFaceTracking, const FaceTracking&());
    MOCK_CONST_METHOD0(GetHeadTracking, const HeadTracking&());
    MOCK_CONST_METHOD0(GetGazeTracking, const GazeTracking&());
};

class FatigueFixture : public ::testing::Test
{
  public:
    FatigueFixture()
        : parameters_{}, mocked_data_source_{}, fatigue_{parameters_, mocked_data_source_}, driver_camera_system_{}
    {
    }

  protected:
    void SetUp() override
    {
        fatigue_.Init();
        EXPECT_CALL(mocked_data_source_, GetFaceTracking())
            .WillRepeatedly(ReturnRef(driver_camera_system_.face_tracking));
    }
    void TearDown() override { fatigue_.Shutdown(); }

    void UpdateDriverCameraSystem(const DriverCameraSystem& driver_camera_system)
    {
        driver_camera_system_ = driver_camera_system;
    }

    void RunOnce() { fatigue_.ExecuteStep(); }

    const FatigueMessage& GetFatigueMessage() const { return fatigue_.GetFatigueMessage(); }

  private:
    Parameters parameters_;
    ::testing::StrictMock<DataSourceMock> mocked_data_source_;
    Fatigue fatigue_;

    DriverCameraSystem driver_camera_system_;
};
template <typename T>
class FatigueFixtureT : public FatigueFixture, public ::testing::WithParamInterface<T>
{
};

struct TestEyeStateParam
{
    // Given
    FaceTracking face_tracking;

    // Then
    EyeState eye_state;
};

using FatigueFixture_WithEyeState = FatigueFixtureT<TestEyeStateParam>;

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Fatigue, 
    FatigueFixture_WithEyeState, 
    ::testing::Values(
        //                  eye_visible, eye_lid_opening, eye_blink_rate, (expected) eye_state
        TestEyeStateParam{{       true,          1.1_mm,         1.0_Hz}, EyeState::kEyesOpen},
        TestEyeStateParam{{      false,          1.1_mm,         1.0_Hz}, EyeState::kEyesUnknown},
        TestEyeStateParam{{       true,          1.1_mm,        11.0_Hz}, EyeState::kEyesUnknown},
        TestEyeStateParam{{       true,          1.0_mm,         1.0_Hz}, EyeState::kEyesClosed},
        TestEyeStateParam{{       true,         10.0_mm,         1.0_Hz}, EyeState::kEyesClosed},
        TestEyeStateParam{{       true,          5.0_mm,         1.0_Hz}, EyeState::kEyesOpen}
));
// clang-format on

TEST_P(FatigueFixture_WithEyeState, Fatigue_GiveTypicalFaceTracking_ExpectUpdatedFatigue)
{
    // Given
    const auto param = GetParam();
    const DriverCameraSystem driver_camera_system =
        DriverCameraSystemBuilder().WithFaceTracking(param.face_tracking).Build();
    UpdateDriverCameraSystem(driver_camera_system);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, param.eye_state));
}

}  // namespace
}  // namespace perception
