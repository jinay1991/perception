///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/common/finite_state_machine.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <functional>

namespace perception
{
namespace
{

using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kDefaultCycleDuration{40ms};

enum class State : std::uint8_t
{
    kInit = 0U,
    kRun = 1U,
    kRelease = 2U,
    kInvalid = 3U
};

class FiniteStateMachineFixture : public ::testing::Test
{
  public:
    FiniteStateMachineFixture() : state_machine_{State::kInit}, time_since_startup_{0ms} {}

  protected:
    using Action = std::function<void()>;

    void SetUp() override
    {
        state_machine_.AddTransition(State::kInit, State::kRun, [&] { return ToRun(); });
        state_machine_.AddTransition(State::kRun, State::kRelease, [&] { return ToRelease(); });

        state_machine_.AddTransition(State::kRun, State::kInit, [&] { return ToInit(); });
        state_machine_.AddTransition(State::kRelease, State::kInit, [&] { return ToInit(); });
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

    void AddStateActions(const State state,
                         const Action& entry_action,
                         const Action& state_action,
                         const Action& exit_action)
    {
        state_machine_.AddStateActions(state, entry_action, state_action, exit_action);
    }

    void AddTransitionAction(const State from_state, const State to_state, const Action& action)
    {
        state_machine_.AddTransitionAction(from_state, to_state, action);
    }

    void Reset() { state_machine_.Reset(); }
    void ResetClock() { time_since_startup_ = 0ms; }

    State GetCurrentState() const { return state_machine_.GetCurrentState(); }

  private:
    bool ToRun() const
    {
        static constexpr std::chrono::milliseconds kTimeTransitionToRun{kDefaultCycleDuration};
        return (time_since_startup_ >= kTimeTransitionToRun);
    }
    bool ToRelease() const
    {
        static constexpr std::chrono::milliseconds kTimeTransitionToRelease{3 * kDefaultCycleDuration};
        return (time_since_startup_ >= kTimeTransitionToRelease);
    }
    bool ToInit() const { return (time_since_startup_ == 0ms); }

    FiniteStateMachine<State> state_machine_;

    std::chrono::milliseconds time_since_startup_;
};

TEST(FiniteStateMachine, FiniteStateMachine_GivenDefaultConstructor_ExpectDefaultState)
{
    // When
    const FiniteStateMachine<State> state_machine{};

    // Then
    EXPECT_THAT(state_machine.GetCurrentState(), static_cast<State>(0U));
    EXPECT_THAT(state_machine.GetCurrentState(), State::kInit);
}

TEST(FiniteStateMachine, FiniteStateMachine_GivenExplicitConstructor_ExpectProvidedInitialState)
{
    // When
    const FiniteStateMachine<State> state_machine{State::kRun};

    // Then
    EXPECT_THAT(state_machine.GetCurrentState(), State::kRun);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenInitializedStateMachine_ExpectInitialState)
{
    // Then
    EXPECT_THAT(GetCurrentState(), State::kInit);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInInitializeState_ExpectTransitionToRunState)
{
    // Given
    ASSERT_THAT(GetCurrentState(), State::kInit);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRun);
}

TEST_F(FiniteStateMachineFixture, FiniteStateMachine_GivenStateMachineInRunState_ExpectTransitionToStopState)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetCurrentState(), State::kRun);

    // When
    RunForDuration(2 * kDefaultCycleDuration);

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRelease);
}

TEST_F(FiniteStateMachineFixture, Reset_GivenStateMachineInRunState_ExpectTransitionToInitState)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetCurrentState(), State::kRun);

    // When
    Reset();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kInit);
}

TEST_F(FiniteStateMachineFixture, AddStateActions_GivenStateActions_ExpectExecutedStateActionsUpOnStateChange)
{
    // Given
    std::int32_t number_of_entries = 0;
    std::int32_t number_of_steps_in_state = 0;
    std::int32_t number_of_exits = 0;
    const auto entry_action = [&number_of_entries] { number_of_entries++; };
    const auto state_action = [&number_of_steps_in_state] { number_of_steps_in_state++; };
    const auto exit_action = [&number_of_exits] { number_of_exits++; };
    AddStateActions(State::kRun, entry_action, state_action, exit_action);
    ASSERT_THAT(GetCurrentState(), State::kInit);

    // When
    RunForDuration(3 * kDefaultCycleDuration);

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRelease);
    EXPECT_THAT(number_of_entries, 1);
    EXPECT_THAT(number_of_exits, 1);
    EXPECT_THAT(number_of_steps_in_state, 1);
}

TEST_F(FiniteStateMachineFixture, AddStateActions_GivenStateActions_ExpectExecutedStateActionsForCurrentState)
{
    // Given
    RunOnce();
    ASSERT_THAT(GetCurrentState(), State::kRun);
    std::int32_t number_of_entries = 0;
    std::int32_t number_of_steps_in_state = 0;
    std::int32_t number_of_exits = 0;
    const auto entry_action = [&number_of_entries] { number_of_entries++; };
    const auto state_action = [&number_of_steps_in_state] { number_of_steps_in_state++; };
    const auto exit_action = [&number_of_exits] { number_of_exits++; };
    AddStateActions(State::kRun, entry_action, state_action, exit_action);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRun);
    EXPECT_THAT(number_of_entries, 0);
    EXPECT_THAT(number_of_exits, 0);
    EXPECT_THAT(number_of_steps_in_state, 1);
}

TEST_F(FiniteStateMachineFixture,
       AddTransitionAction_GivenTransitionAction_ExpectExecutedTransitionActionsUpOnStateChange)
{
    // Given
    std::int32_t number_of_actions = 0;
    AddTransitionAction(State::kInit, State::kRun, [&number_of_actions] { number_of_actions++; });
    ASSERT_THAT(GetCurrentState(), State::kInit);

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetCurrentState(), State::kRun);
    EXPECT_THAT(number_of_actions, 1);
}
}  // namespace
}  // namespace perception
