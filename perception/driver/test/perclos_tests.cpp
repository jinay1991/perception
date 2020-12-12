///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/perclos.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace
{
using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kDefaultStepDuration{40U};

class PerclosFixture : public ::testing::Test
{
  public:
    PerclosFixture() : perclos_{} {}

  protected:
    void RunForDuration(const EyeState& eye_state,
                        const std::chrono::milliseconds duration,
                        const std::chrono::milliseconds step = kDefaultStepDuration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += step)
        {
            perclos_.Calculate(eye_state);
        }
    }
    double GetCurrentPercentage() const { return perclos_.GetCurrentPercentage(); }

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
    double percentage;
};

using PerclosFixture_WithEyeStateDuration = PerclosFixtureT<TestEyeStateDurationParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Perclos, 
    PerclosFixture_WithEyeStateDuration, 
    ::testing::Values(
        //                        eye_state            , duration, (expected) percentage_closure
        TestEyeStateDurationParam{EyeState::kEyesClosed,     2min,                           0.0}
));
// clang-format on

TEST_P(PerclosFixture_WithEyeStateDuration, Calculate_GivenEyeStateClosedForTypicalDuration_ExpectPercentageClosure)
{
    // Given
    const auto param = GetParam();

    // When
    RunForDuration(param.eye_state, param.duration);

    // Then
    EXPECT_DOUBLE_EQ(param.percentage, GetCurrentPercentage());
}
}  // namespace
}  // namespace perception
