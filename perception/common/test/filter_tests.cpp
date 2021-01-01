///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "perception/common/filter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>

namespace perception
{
namespace
{

enum class State : std::uint8_t
{
    kState_0 = 0U,
    kState_1 = 1U,
    kState_2 = 2U,
    kState_3 = 3U,
    kInvalid = 4U
};

class FilterFixture : public ::testing::Test
{
  public:
    FilterFixture() : filter_{State::kInvalid}, delta_duration_{40ms} {}

  protected:
    void SetHoldDuration(const std::chrono::milliseconds duration) { filter_.SetHoldDuration(duration); }

    void RunOnce(const State new_state) { filter_.Update(new_state, delta_duration_); }

    void RunAndCheckForDuration(const State new_state,
                                const std::chrono::milliseconds duration,
                                const std::function<void()>& check)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += delta_duration_)
        {
            RunOnce(new_state);
            SCOPED_TRACE("\ntime passed: " + std::to_string(time_passed.count()) +
                         "ms, total duration: " + std::to_string(duration.count()) + "ms.");
            check();
        }
    }

    void RunForDuration(const State new_state, const std::chrono::milliseconds duration)
    {
        RunAndCheckForDuration(new_state, duration, [] {});
    }

    void ChangeState(const State state)
    {
        RunOnce(State::kInvalid);  // enables immediate change state
        RunOnce(state);
        ASSERT_THAT(GetCurrentState(), state);
    }

    State GetCurrentState() const { return filter_.GetCurrentState(); }
    std::chrono::milliseconds GetDeltaDuration() const { return delta_duration_; }

  private:
    Filter<State> filter_;

    const std::chrono::milliseconds delta_duration_;
};

template <typename T>
class FilterFixtureT : public FilterFixture, public ::testing::WithParamInterface<T>
{
};

using FilterFixture_WithState = FilterFixtureT<State>;

INSTANTIATE_TEST_SUITE_P(
    Filter,
    FilterFixture_WithState,
    ::testing::Values(State::kState_0, State::kState_1, State::kState_2, State::kState_3, State::kInvalid));

TEST_P(FilterFixture_WithState, ChangeState_GivenTypicalState_ExpectChangedState)
{
    // Given
    const auto state = GetParam();

    // When
    ChangeState(state);

    // Then
    EXPECT_THAT(GetCurrentState(), state);
}

TEST_F(FilterFixture, Update_GivenInvalidCurrentState_ExpectChangedState)
{
    // Given
    const auto new_state = State::kState_0;
    ChangeState(State::kInvalid);

    // When
    RunOnce(new_state);

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}

TEST_F(FilterFixture, Update_GivenInvalidNewState_ExpectChangedState)
{
    // Given
    const auto new_state = State::kInvalid;
    ChangeState(State::kState_0);

    // When
    RunOnce(new_state);

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}

TEST_F(FilterFixture, Update_GivenValidNewStateAndZeroHoldTime_ExpectChangedState)
{
    // Given
    const auto new_state = State::kState_2;
    SetHoldDuration(0ms);
    ChangeState(State::kState_0);

    // When
    RunOnce(new_state);

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}

TEST_F(FilterFixture, Update_GivenValidNewStateAndNonZeroHoldTime_ExpectHeldState)
{
    // Given
    const auto initial_state = State::kState_0;
    const auto new_state = State::kState_1;
    const auto hold_duration = 120ms;
    ChangeState(initial_state);
    SetHoldDuration(hold_duration);

    // When/Then
    RunAndCheckForDuration(new_state, hold_duration, [this] { EXPECT_THAT(GetCurrentState(), initial_state); });
}

TEST_F(FilterFixture, Update_GivenValidNewStateAndNonZeroHoldTime_ExpectChangedStateAfterHold)
{
    // Given
    const auto initial_state = State::kState_0;
    const auto new_state = State::kState_1;
    const auto hold_duration = 80ms;
    ChangeState(initial_state);
    SetHoldDuration(hold_duration);

    // When
    RunForDuration(new_state, hold_duration + GetDeltaDuration());

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}

TEST_F(FilterFixture, Update_GivenValidSameNewStateAndNonZeroHoldTime_ExpectNoChange)
{
    // Given
    const auto initial_state = State::kState_1;
    const auto new_state = State::kState_1;
    const auto hold_duration = 80ms;
    ChangeState(initial_state);
    SetHoldDuration(hold_duration);

    // When
    RunForDuration(new_state, hold_duration + GetDeltaDuration());

    // Then
    EXPECT_THAT(GetCurrentState(), initial_state);
}
}  // namespace
}  // namespace perception
