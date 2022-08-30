///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/perclos.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace driver
{
namespace
{

class PerclosFixture : public ::testing::Test
{
  public:
    PerclosFixture() : perclos_{} {}

  protected:
    void RunOnce(const EyeState& eye_state) { perclos_.Calculate(eye_state); }

    void RunForDuration(const EyeState& eye_state, const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kMaxCycleDuration)
        {
            RunOnce(eye_state);
        }
    }

    double GetClosurePercentage() const { return perclos_.GetClosurePercentage(); }
    double GetAvailabilityPercentage() const { return perclos_.GetAvailabilityPercentage(); }

    void SetEyeStateObservationDuration(const std::chrono::milliseconds duration)
    {
        perclos_.SetEyeStateObservationDuration(duration);
    }
    std::chrono::milliseconds GetEyeStateObservationDuration() const
    {
        return perclos_.GetEyeStateObservationDuration();
    }

  private:
    Perclos perclos_;
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

struct TestEyeStateObservationDurationParam
{
    // Given
    std::chrono::milliseconds eye_state_observation_duration;

    // Then
    std::chrono::milliseconds changed_eye_state_observation_duration;
};

using PerclosFixture_WithEyeStateObservationDuration = PerclosFixtureT<TestEyeStateObservationDurationParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Perclos,
    PerclosFixture_WithEyeStateObservationDuration,
    ::testing::Values(
        ///                                    eye_state_observation_duration     , (expected) changed_eye_state_observation_duration
        TestEyeStateObservationDurationParam{  kMaxEyeStateObservationDuration / 2, kMaxEyeStateObservationDuration / 2}, // observe change
        TestEyeStateObservationDurationParam{kMaxEyeStateObservationDuration + 1ms, kMaxEyeStateObservationDuration    }  // no change
));
// clang-format on

TEST_P(PerclosFixture_WithEyeStateObservationDuration,
       SetEyeStateObservationDuration_GivenTypicalEyeStateObservationDuration_ExpectUpdatedEyeStateObservationDuration)
{
    // Given
    const auto param = GetParam();

    // When
    SetEyeStateObservationDuration(param.eye_state_observation_duration);

    // Then
    EXPECT_THAT(GetEyeStateObservationDuration(), param.changed_eye_state_observation_duration);
}

TEST_F(PerclosFixture, GetEyeStateObservationDuration_GivenInitializedPerclos_ExpectMaxEyeStateObservationDuration)
{
    // Then
    EXPECT_THAT(GetEyeStateObservationDuration(), kMaxEyeStateObservationDuration);
}
}  // namespace
}  // namespace driver
}  // namespace perception
