///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/distraction_detector.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

#include <cmath>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::DoubleNear;
using ::testing::Field;
using ::testing::ReturnRef;

constexpr std::chrono::milliseconds kDefaultStepDuration{40ms};

class DistractionDetectorFixture : public ::testing::Test
{
  public:
    DistractionDetectorFixture()
        : mocked_data_source_{}, mocked_parameter_handler_{}, detector_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void RunOnce() { detector_.Step(); }

    void RunForDuration(const GazeTracking& gaze_tracking,
                        const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kDefaultStepDuration)
    {
        EXPECT_CALL(mocked_data_source_, GetGazeTracking()).WillRepeatedly(ReturnRef(gaze_tracking));

        for (auto time_passed = 0ms; time_passed < duration; time_passed += step)
        {
            RunOnce();
        }
    }

    DistractionState GetDistractionState() const { return detector_.GetDistractionState(); }
    double GetDistractionConfidence() const { return detector_.GetDistractionConfidence(); }

  private:
    ::testing::StrictMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    DistractionDetector detector_;
};

template <typename T>
class DistractionDetectorFixtureT : public DistractionDetectorFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(DistractionDetectorFixture, Step_GivenTypicalDataSource_ExpectDistractionStateAndConfidence)
{
    // When
    RunOnce();

    // Then
    EXPECT_EQ(GetDistractionState(), DistractionState::kNotDistracted);
    EXPECT_DOUBLE_EQ(GetDistractionConfidence(), 0.0);
}

TEST_F(DistractionDetectorFixture, Step_GivenTypicalGazeTracking_ExpectDistractionStateAndConfidence)
{
    // Given
    const GazeTracking gaze_tracking{1.0_rad, 14.0_rad, 100.0_rad};

    // When
    RunForDuration(gaze_tracking, 50ms);

    // Then
    EXPECT_EQ(GetDistractionState(), DistractionState::kNotDistracted);
    EXPECT_DOUBLE_EQ(GetDistractionConfidence(), 0.0);
}
}  // namespace
}  // namespace driver
}  // namespace perception
