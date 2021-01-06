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
    kState_Init = 0U,
    kState_Ready = 1U,
    kState_Run = 2U,
    kState_Stop = 3U,
    kState_Release = 4U,
    kInvalid = 5U
};

class FiniteStateMachineFixture : public ::testing::Test
{
  public:
    FiniteStateMachineFixture() : state_machine_{State::kState_Init}, time_since_startup_{0ms} {}

  protected:
    void SetUp() override
    {
        state_machine_.AddTransition(State::kState_Init, State::kState_Ready, [&] { return ToReady(); });
        state_machine_.AddTransition(State::kState_Ready, State::kState_Run, [&] { return ToRun(); });
        state_machine_.AddTransition(State::kState_Run, State::kState_Stop, [&] { return ToStop(); });
        state_machine_.AddTransition(State::kState_Stop, State::kState_Release, [&] { return ToRelease(); });
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
    bool ToRelease() const { return time_since_startup_ >= (4 * kDefaultCycleDuration); }

    FiniteStateMachine<State> state_machine_;

    std::chrono::milliseconds time_since_startup_;
};

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInInitializeState_ExpectTransitionToReadyState)
{
    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_Ready);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInReadyState_ExpectTransitionToRunState)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetCurrentState(), State::kState_Ready);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_Run);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInRunState_ExpectTransitionToStopState)
{
    // Given
    RunForDuration(2 * kDefaultCycleDuration);
    ASSERT_THAT(GetCurrentState(), State::kState_Run);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_Stop);
}
}  // namespace
}  // namespace perception
