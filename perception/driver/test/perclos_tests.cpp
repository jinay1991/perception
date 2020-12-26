///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/common/current_previous.h"
#include "perception/common/toggle.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/perclos.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace
{

TEST(Perclos, GlobalConstants)
{
    // Then
    EXPECT_THAT(kAssumedCycleDuration, 40ms);
    EXPECT_THAT(kMaxLongtermStorageSize, kMaxEyeStateObservationDuration / kAssumedCycleDuration);
}

class PerclosFixture : public ::testing::Test
{
  public:
    PerclosFixture() : parameter_handler_{}, perclos_{}, eye_state_toggle_{EyeState::kEyesOpen, EyeState::kEyesClosed}
    {
    }

  protected:
    void SetUp() override { perclos_.UpdateParameters(parameter_handler_); }

    void RunOnce(const EyeState& eye_state) { perclos_.Calculate(eye_state); }

    void RunForDuration(const EyeState& eye_state, const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kAssumedCycleDuration)
        {
            RunOnce(eye_state);
        }
    }

    void RunWithEyeToggleForDuration(const std::chrono::milliseconds duration)
    {
        eye_state_toggle_.SetToggleDuration(parameter_handler_.GetEyeBlinkDuration());

        for (auto time_passed = 0ms; time_passed < duration; time_passed += kAssumedCycleDuration)
        {
            eye_state_toggle_.Update(kAssumedCycleDuration);
            RunOnce(eye_state_toggle_.GetCurrentState());
        }
    }

    ParameterHandler& GetParameterHandler() { return parameter_handler_; }

    double GetClosurePercentage() const { return perclos_.GetClosurePercentage(); }
    double GetAvailabilityPercentage() const { return perclos_.GetAvailabilityPercentage(); }

  private:
    ParameterHandler parameter_handler_;
    Perclos perclos_;

    Toggle<EyeState> eye_state_toggle_;
};

template <typename T>
class PerclosFixtureT : public PerclosFixture, public ::testing::WithParamInterface<T>
{
};

struct TestEyeStateDurationParam
{
    // Given
    EyeState eye_state;
    std::chrono::milliseconds duration;

    // Then
    double closure_percentage;
    double availability_percentage;
};

using PerclosFixture_WithEyeStateDuration = PerclosFixtureT<TestEyeStateDurationParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Perclos, 
    PerclosFixture_WithEyeStateDuration, 
    ::testing::Values(
        //                        eye_state            , duration, (expected) closure_percentage, (expected) availability_percentage
        TestEyeStateDurationParam{EyeState::kEyesClosed,     2min,                         100.0,                               40.0},
        TestEyeStateDurationParam{EyeState::kEyesClosed,     5min,                         100.0,                              100.0},
        TestEyeStateDurationParam{  EyeState::kEyesOpen,     2min,                           0.0,                               40.0},
        TestEyeStateDurationParam{  EyeState::kEyesOpen,     5min,                           0.0,                              100.0},
        TestEyeStateDurationParam{  EyeState::kEyesOpen,     0min,                           0.0,                                0.0},
        TestEyeStateDurationParam{  EyeState::kEyesOpen,     6min,                           0.0,                              100.0},
        TestEyeStateDurationParam{EyeState::kEyesClosed,     6min,                         100.0,                              100.0}
));
// clang-format on

TEST_P(PerclosFixture_WithEyeStateDuration, Calculate_GivenEyeStateClosedForTypicalDuration_ExpectPercentageClosure)
{
    // Given
    const auto param = GetParam();

    // When
    RunForDuration(param.eye_state, param.duration);

    // Then
    EXPECT_THAT(GetClosurePercentage(), param.closure_percentage);
    EXPECT_THAT(GetAvailabilityPercentage(), param.availability_percentage);
}

TEST_F(PerclosFixture, Calculate_GivenEyeBlinkRate_ExpectPercentageClosure)
{
    // Given
    GetParameterHandler().SetEyeBlinkRate(10.0_Hz);

    // When
    RunWithEyeToggleForDuration(2min);

    // Then
    EXPECT_THAT(GetClosurePercentage(), 50.0);
    EXPECT_THAT(GetAvailabilityPercentage(), 40.0);
}
}  // namespace
}  // namespace perception
