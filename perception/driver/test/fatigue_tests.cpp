///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

#include <cmath>

namespace perception
{
namespace
{
using ::testing::Field;
using ::testing::Return;

constexpr std::chrono::milliseconds kDefaultStepDuration{40U};

class FatigueFixture : public ::testing::Test
{
  public:
    FatigueFixture()
        : mocked_data_source_{}, mocked_parameter_handler_{}, fatigue_{mocked_parameter_handler_, mocked_data_source_}
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

    void RunOnce() { fatigue_.Step(); }

    void RunForDuration(const EyeState& eye_state,
                        const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kDefaultStepDuration)
    {
        const auto eye_lid_opening = (EyeState::kEyesOpen == eye_state) ? 0.0_mm : kMaxEyeLidOpening;
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

    const FatigueMessage& GetFatigueMessage() const { return fatigue_.GetFatigueMessage(); }

    ::testing::StrictMock<mock::DataSourceMock> mocked_data_source_;

  private:
    ::testing::StrictMock<mock::ParameterHandlerMock> mocked_parameter_handler_;
    Fatigue fatigue_;
};

template <typename T>
class FatigueFixtureT : public FatigueFixture, public ::testing::WithParamInterface<T>
{
};


TEST_F(FatigueFixture, DISABLED_Fatigue_GivenEyesOpenForDuration_ExpectAwakeFatigueLevel)
{
    // Given
    const auto eye_state = EyeState::kEyesOpen;
    const auto duration = 2min;

    // When
    RunForDuration(eye_state, duration);

    // Then
    EXPECT_THAT(GetFatigueMessage(),
                AllOf(Field(&FatigueMessage::level, FatigueLevel::kAwake), Field(&FatigueMessage::confidence, 100.0)));
}
}  // namespace
}  // namespace perception
