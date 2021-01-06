///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/common/finite_state_machine.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

namespace perception
{
namespace
{

using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kDefaultCycleDuration{40ms};

enum class State : std::uint8_t
{
    kInitialize = 0U,
    kReady = 1U,
    kRun = 2U,
    kStop = 3U,
    kRelease = 4U,
    kInvalid = 5U
};

class FiniteStateMachineFixture : public ::testing::Test
{
  public:
    FiniteStateMachineFixture() : state_machine_{State::kInitialize}, time_since_startup_{0ms} {}

  protected:
    void SetUp() override
    {
        state_machine_.AddTransition(State::kInitialize, State::kReady, [&] { return ToReady(); });
        state_machine_.AddTransition(State::kReady, State::kRun, [&] { return ToRun(); });
        state_machine_.AddTransition(State::kRun, State::kStop, [&] { return ToStop(); });
    }

    void RunOnce()
    {
        time_since_startup_ += kDefaultCycleDuration;
        state_machine_.Step();
    }

    void RunForDuration(const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += kDefaultCycleDuration)
        {
            RunOnce();
        }
    }

    State GetCurrentState() const { return state_machine_.GetCurrentState(); }

  private:
    bool ToReady() const { return time_since_startup_ >= kDefaultCycleDuration; }
    bool ToRun() const { return time_since_startup_ >= (2 * kDefaultCycleDuration); }
    bool ToStop() const { return time_since_startup_ >= (3 * kDefaultCycleDuration); }

    FiniteStateMachine<State> state_machine_;

    std::chrono::milliseconds time_since_startup_;
};

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInInitializeState_ExpectTransitionToReadyState)
{
    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kReady);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInReadyState_ExpectTransitionToRunState)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetCurrentState(), State::kReady);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRun);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInRunState_ExpectTransitionToStopState)
{
    // Given
    RunForDuration(2 * kDefaultCycleDuration);
    ASSERT_THAT(GetCurrentState(), State::kRun);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kStop);
}
}  // namespace
}  // namespace perception
