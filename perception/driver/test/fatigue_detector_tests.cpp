///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/fatigue_detector.h"
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
using ::testing::Return;

constexpr std::chrono::milliseconds kDefaultStepDuration{40ms};

class FatigueDetectorFixture : public ::testing::Test
{
  public:
    FatigueDetectorFixture()
        : mocked_data_source_{}, mocked_parameter_handler_{}, detector_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void SetUp() override
    {
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeLidOpening()).WillRepeatedly(Return(kMaxEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeLidOpening()).WillRepeatedly(Return(kMinEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeBlinkRate()).WillRepeatedly(Return(kMinEyeBlinkRate));
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));
    }

    void RunOnce() { detector_.Step(); }

    void RunForDuration(const EyeState& eye_state,
                        const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kDefaultStepDuration)
    {
        const auto eye_lid_opening = (EyeState::kEyesClosed == eye_state) ? 0.0_mm : kMaxEyeLidOpening;
        const std::chrono::milliseconds eye_blink_duration =
            std::chrono::seconds{static_cast<std::uint32_t>(std::floor(1.0 / kMaxEyeBlinkRate.value()))};
        EXPECT_CALL(mocked_data_source_, IsFaceVisible()).WillRepeatedly(Return(true));
        EXPECT_CALL(mocked_data_source_, IsEyeVisible()).WillRepeatedly(Return(true));
        EXPECT_CALL(mocked_data_source_, GetEyeLidOpening()).WillRepeatedly(Return(eye_lid_opening));
        EXPECT_CALL(mocked_data_source_, GetEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));
        EXPECT_CALL(mocked_data_source_, GetEyeBlinkDuration()).WillRepeatedly(Return(eye_blink_duration));

        for (auto time_passed = 0ms; time_passed < duration; time_passed += step)
        {
            RunOnce();
        }
    }

    FatigueState GetFatigueState() const { return detector_.GetFatigueState(); }
    double GetFatigueConfidence() const { return detector_.GetFatigueConfidence(); }

  private:
    ::testing::NiceMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    FatigueDetector detector_;
};

template <typename T>
class FatigueDetectorFixtureT : public FatigueDetectorFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(FatigueDetectorFixture, Step_GivenTypicalDataSource_ExpectFatigueStateAndConfidence)
{
    // When
    RunOnce();

    // Then
    EXPECT_EQ(GetFatigueState(), FatigueState::kAwake);
    EXPECT_NEAR(GetFatigueConfidence(), 0.00013, 0.00001);
}

TEST_F(FatigueDetectorFixture, Step_GivenTypicalEyeState_ExpectFatigueStateAndConfidence)
{
    // Given
    const EyeState eye_state{EyeState::kEyesOpen};

    // When
    RunForDuration(eye_state, 5min);

    // Then
    EXPECT_EQ(GetFatigueState(), FatigueState::kAwake);
    EXPECT_DOUBLE_EQ(GetFatigueConfidence(), 1.0);
}
}  // namespace
}  // namespace driver
}  // namespace perception
