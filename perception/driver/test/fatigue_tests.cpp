///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
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
namespace driver
{
namespace
{
using ::testing::DoubleNear;
using ::testing::Field;
using ::testing::Return;

constexpr std::chrono::milliseconds kDefaultStepDuration{40ms};

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

    const FatigueMessage& GetFatigueMessage() const { return fatigue_.GetFatigueMessage(); }

  private:
    ::testing::StrictMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    Fatigue fatigue_;
};

template <typename T>
class FatigueFixtureT : public FatigueFixture, public ::testing::WithParamInterface<T>
{
};

struct TestEyeStateDurationParam
{
    // Given
    EyeState eye_state;
    std::chrono::milliseconds duration;

    // Then
    FatigueState state;
    double confidence;
};

using FatigueFixture_WithEyeClosedForDuration = FatigueFixtureT<TestEyeStateDurationParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
  Fatigue,
  FatigueFixture_WithEyeClosedForDuration,
  ::testing::Values(
    //                         eye_state           , duration,       (expected) state       , (expected) confidence
    TestEyeStateDurationParam{EyeState::kEyesOpen  ,     5min, FatigueState::kAwake         ,                 1.0  }, // (0)
    TestEyeStateDurationParam{EyeState::kEyesOpen  ,     6min, FatigueState::kAwake         ,                 1.0  }, // (1)
    TestEyeStateDurationParam{EyeState::kEyesOpen  ,     0min, FatigueState::kInvalid       ,                 0.0  }, // (2)
    TestEyeStateDurationParam{EyeState::kEyesOpen  ,     2min, FatigueState::kAwake         ,                 0.4  }, // (3)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     0min, FatigueState::kInvalid       ,                 0.0  }, // (4)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     5min, FatigueState::kSleep         ,                 1.0  }, // (5)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     6min, FatigueState::kSleep         ,                 1.0  }, // (6)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     4min, FatigueState::kSleep         ,                 0.8  }, // (7)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     2min, FatigueState::kBeginningSleep,                 0.4  }, // (8)
    TestEyeStateDurationParam{EyeState::kEyesClosed,     1min, FatigueState::kDrowsy        ,                 0.2  }, // (9)
    TestEyeStateDurationParam{EyeState::kEyesClosed,      30s, FatigueState::kQuestionable  ,                 0.1  }, // (10)
    TestEyeStateDurationParam{EyeState::kEyesClosed,      10s, FatigueState::kAwake         ,                 0.033}  // (11)
  ));
// clang-format on

TEST_P(FatigueFixture_WithEyeClosedForDuration, Fatigue_GivenTypicalEyeStateForDuration_ExpectUpdatedFatigueProperties)
{
    // Given
    const auto param = GetParam();

    // When
    RunForDuration(param.eye_state, param.duration);

    // Then
    EXPECT_THAT(GetFatigueMessage(),
                AllOf(Field(&FatigueMessage::state, param.state),
                      Field(&FatigueMessage::confidence, DoubleNear(param.confidence, 0.1))));
}
}  // namespace
}  // namespace driver
}  // namespace perception
