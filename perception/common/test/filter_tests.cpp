///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/common/filter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>

namespace perception
{
namespace
{

class FilterFixture : public ::testing::Test
{
  public:
    FilterFixture() : filter_{0}, delta_duration_{40ms} {}

  protected:
    void SetHoldDuration(const std::chrono::milliseconds duration) { filter_.SetHoldDuration(duration); }

    void RunOnce(const std::int32_t new_state) { filter_.Update(new_state, delta_duration_); }

    void RunAndCheckForDuration(const std::int32_t new_state,
                                const std::chrono::milliseconds duration,
                                const std::function<void()>& check)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += delta_duration_)
        {
            RunOnce(new_state);
            SCOPED_TRACE("\ntime_passed: " + std::to_string(time_passed.count()) +
                         "ms, duration: " + std::to_string(duration.count()) + "ms.");
            check();
        }
    }

    void RunForDuration(const std::int32_t new_state, const std::chrono::milliseconds duration)
    {
        RunAndCheckForDuration(new_state, duration, [] {});
    }

    std::int32_t GetCurrentState() const { return filter_.GetCurrentState(); }
    std::chrono::milliseconds GetDeltaDuration() const { return delta_duration_; }

  private:
    Filter<std::int32_t> filter_;

    const std::chrono::milliseconds delta_duration_;
};

TEST_F(FilterFixture, GivenZeroHoldDuration_ExpectUpdatedStateImmediately)
{
    // Given
    const auto new_state = 1;
    SetHoldDuration(0ms);

    // When
    RunOnce(new_state);

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}

TEST_F(FilterFixture, GivenTypicalHoldDuration_ExpectUpdatedStateAfterHoldDuration)
{
    // Given
    const auto new_state = 1;
    const auto delta_duration = GetDeltaDuration();
    SetHoldDuration(delta_duration + 10ms);

    // When
    RunAndCheckForDuration(new_state, delta_duration, [this] { ASSERT_THAT(GetCurrentState(), 0); });
    RunOnce(new_state);

    // Then
    EXPECT_THAT(GetCurrentState(), new_state);
}
}  // namespace
}  // namespace perception