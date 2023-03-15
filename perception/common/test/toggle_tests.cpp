///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/common/toggle.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{
using namespace std::chrono_literals;

constexpr std::chrono::milliseconds kStateToggleDuration{80ms};

enum class State : std::uint8_t
{
    kState_ON = 0U,
    kState_OFF = 1U,
    kInvalid = 2U
};

class ToggleFixture : public ::testing::Test
{
  public:
    ToggleFixture() : state_toggle_{State::kState_ON, State::kState_OFF}, delta_duration_{40ms} {}

  protected:
    void SetUp() override { state_toggle_.SetToggleDuration(kStateToggleDuration); }

    void RunOnce() { state_toggle_.Update(delta_duration_); }

    void RunForDuration(const std::chrono::milliseconds duration)
    {
        RunAndCheckForDuration(duration, [] {});
    }

    void RunAndCheckForDuration(const std::chrono::milliseconds duration, const std::function<void()> check)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += delta_duration_)
        {
            RunOnce();
            SCOPED_TRACE("\ntime passed: " + std::to_string(time_passed.count()) +
                         "ms, total duration: " + std::to_string(duration.count()) + "ms.");
            check();
        }
    }

    void StateOFF() { ASSERT_THAT(GetCurrentState(), State::kState_OFF); }

    void StateON()
    {
        RunForDuration(kStateToggleDuration + GetDeltaDuration());
        ASSERT_THAT(GetCurrentState(), State::kState_ON);
    }
    void SetToggleDuration(const std::chrono::milliseconds duration) { state_toggle_.SetToggleDuration(duration); }

    std::chrono::milliseconds GetDeltaDuration() const { return delta_duration_; }
    State GetCurrentState() const { return state_toggle_.GetCurrentState(); }

  private:
    Toggle<State> state_toggle_;
    std::chrono::milliseconds delta_duration_;
};

TEST_F(ToggleFixture, SetToggleDuration_GivenStateOFF_ExpectToggleBasedOnToggleDuration)
{
    // Given
    StateOFF();
    const std::chrono::milliseconds toggle_duration = 80ms;
    SetToggleDuration(toggle_duration);

    // When
    RunForDuration(toggle_duration + GetDeltaDuration());

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_ON);
}

TEST_F(ToggleFixture, Update_GivenStateOFF_ExpectToggleAfterToggleDuration)
{
    // Given
    StateOFF();

    // When
    RunForDuration(kStateToggleDuration + GetDeltaDuration());

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_ON);
}

TEST_F(ToggleFixture, Update_GivenStateON_ExpectToggleAfterToggleDuration)
{
    // Given
    StateON();

    // When
    RunForDuration(kStateToggleDuration + GetDeltaDuration());

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_OFF);
}

TEST_F(ToggleFixture, Update_GivenStateON_ExpectNoToggleBeforeToggleDuration)
{
    // Given
    StateON();

    // When
    RunForDuration(kStateToggleDuration);

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_ON);
}

TEST_F(ToggleFixture, Update_GivenStateOFF_ExpectNoToggleBeforeToggleDuration)
{
    // Given
    StateOFF();

    // When
    RunForDuration(kStateToggleDuration);

    // Then
    EXPECT_THAT(GetCurrentState(), State::kState_OFF);
}

TEST_F(ToggleFixture, Update_GivenStateON_ExpectNoToggleTillToggleDuration)
{
    // Given
    StateON();

    // When
    RunAndCheckForDuration(kStateToggleDuration, [this] { EXPECT_THAT(GetCurrentState(), State::kState_ON); });
}

TEST_F(ToggleFixture, Update_GivenStateOFF_ExpectNoToggleTillToggleDuration)
{
    // Given
    StateOFF();

    // When/Then
    RunAndCheckForDuration(kStateToggleDuration, [this] { EXPECT_THAT(GetCurrentState(), State::kState_OFF); });
}
}  // namespace
}  // namespace perception
