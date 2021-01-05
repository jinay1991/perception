///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/driver/test/support/mocks/data_source_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace mock
{
namespace
{
using ::testing::Return;
using ::testing::ReturnRef;

class DataSourceMockFixture : public ::testing::Test
{
  public:
    DataSourceMockFixture() : mocked_data_source_{} {}

  protected:
    ::testing::NiceMock<DataSourceMock> mocked_data_source_;
};

template <typename T>
class DataSourceMockFixtureT : public DataSourceMockFixture, public ::testing::WithParamInterface<T>
{
};

using DataSourceMockFixture_WithBool = DataSourceMockFixtureT<bool>;

INSTANTIATE_TEST_SUITE_P(DataSourceMock, DataSourceMockFixture_WithBool, ::testing::Bool());

TEST_P(DataSourceMockFixture_WithBool, IsFaceVisible_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto is_face_visible = GetParam();
    EXPECT_CALL(mocked_data_source_, IsFaceVisible()).WillRepeatedly(Return(is_face_visible));

    // When
    const auto result = mocked_data_source_.IsFaceVisible();

    // Then
    EXPECT_THAT(result, is_face_visible);
}

TEST_P(DataSourceMockFixture_WithBool, IsEyeVisible_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto is_eye_visible = GetParam();
    EXPECT_CALL(mocked_data_source_, IsEyeVisible()).WillRepeatedly(Return(is_eye_visible));

    // When
    const auto result = mocked_data_source_.IsEyeVisible();

    // Then
    EXPECT_THAT(result, is_eye_visible);
}

TEST_F(DataSourceMockFixture, GetEyeBlinkDuration_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_duration = 10ms;
    EXPECT_CALL(mocked_data_source_, GetEyeBlinkDuration()).WillRepeatedly(Return(eye_duration));

    // When
    const auto result = mocked_data_source_.GetEyeBlinkDuration();

    // Then
    EXPECT_THAT(result, eye_duration);
}

TEST_F(DataSourceMockFixture, GetEyeBlinkRate_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_blink_rate = 10.0_Hz;
    EXPECT_CALL(mocked_data_source_, GetEyeBlinkRate()).WillRepeatedly(Return(eye_blink_rate));

    // When
    const auto result = mocked_data_source_.GetEyeBlinkRate();

    // Then
    EXPECT_THAT(result, eye_blink_rate);
}

TEST_F(DataSourceMockFixture, GetEyeLidOpening_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_lid_opening = 1.0_mm;
    EXPECT_CALL(mocked_data_source_, GetEyeLidOpening()).WillRepeatedly(Return(eye_lid_opening));

    // When
    const auto result = mocked_data_source_.GetEyeLidOpening();

    // Then
    EXPECT_THAT(result, eye_lid_opening);
}

TEST_F(DataSourceMockFixture, GetHeadTracking_GivenTypicalValue_ExpectSame)
{
    // Given
    const HeadTracking head_tracking{10.0_rad, 1.0_rad, -1.0_rad};
    EXPECT_CALL(mocked_data_source_, GetHeadTracking()).WillRepeatedly(ReturnRef(head_tracking));

    // When
    const auto result = mocked_data_source_.GetHeadTracking();

    // Then
    EXPECT_THAT(result, head_tracking);
}

TEST_F(DataSourceMockFixture, GetGazeTracking_GivenTypicalValue_ExpectSame)
{
    // Given
    const GazeTracking gaze_tracking{10.0_rad, 1.0_rad, -1.0_rad};
    EXPECT_CALL(mocked_data_source_, GetGazeTracking()).WillRepeatedly(ReturnRef(gaze_tracking));

    // When
    const auto result = mocked_data_source_.GetGazeTracking();

    // Then
    EXPECT_THAT(result, gaze_tracking);
}

TEST_F(DataSourceMockFixture, GetTimePoint_GivenTypicalValue_ExpectSame)
{
    // Given
    const std::chrono::system_clock::time_point time_point{10ms};
    EXPECT_CALL(mocked_data_source_, GetTimePoint()).WillRepeatedly(Return(time_point));

    // When
    const auto result = mocked_data_source_.GetTimePoint();

    // Then
    EXPECT_THAT(result, time_point);
}
}  // namespace
}  // namespace mock
}  // namespace perception