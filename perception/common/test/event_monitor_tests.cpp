///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/common/event_monitor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <initializer_list>

namespace perception
{
namespace
{
constexpr std::int32_t kAcceptableEvents{5};
constexpr std::int32_t kRecuperableEvents{4};
constexpr std::int32_t kEventMonitorSize{10};

class EventMonitorFixture : public ::testing::Test
{
  public:
    EventMonitorFixture() : event_monitor_{} {}

  protected:
    void SetUp() override
    {
        event_monitor_.SetAcceptableEvents(kAcceptableEvents);
        event_monitor_.SetRecuperableEvents(kRecuperableEvents);
    }

    void RunOnce(const bool is_event_occurred) { event_monitor_.RecordEvent(is_event_occurred); }

    void RunFor(const std::initializer_list<bool> event_list)
    {
        for (const auto& event : event_list)
        {
            RunOnce(event);
        }
    }

    void RunForIterations(const std::int32_t iterations, const bool is_event_occurred)
    {
        const auto check = [] {};
        RunAndCheckForIterations(iterations, is_event_occurred, check);
    }

    void RunAndCheckForIterations(const std::int32_t iterations,
                                  const bool is_event_occurred,
                                  const std::function<void()>& check)
    {
        for (auto i = 0; i < iterations; ++i)
        {
            RunOnce(is_event_occurred);
            SCOPED_TRACE("total of " + std::to_string(i) + " iteration(s) completed out of " +
                         std::to_string(iterations) + " iteration(s).");
            check();
        }
    }

    inline constexpr bool IsTriggerConditionMet() const { return event_monitor_.IsTriggerConditionMet(); }
    inline constexpr bool IsResetConditionMet() const { return event_monitor_.IsResetConditionMet(); }

  private:
    EventMonitor<kEventMonitorSize> event_monitor_;
};

TEST_F(EventMonitorFixture, EventMonitor_GivenContinuousTriggerredEvents_ExpectTriggerConditionMet)
{
    // Given
    RunAndCheckForIterations(kAcceptableEvents, true, [this] { ASSERT_FALSE(IsTriggerConditionMet()); });

    // When
    RunOnce(true);

    // Then
    EXPECT_TRUE(IsTriggerConditionMet());
}

TEST_F(EventMonitorFixture, EventMonitor_GivenContinuousTriggerredEvents_ExpectResetConditionMet)
{
    // Given
    RunForIterations(kEventMonitorSize, true);
    ASSERT_TRUE(IsTriggerConditionMet());
    ASSERT_FALSE(IsResetConditionMet());

    // When
    RunForIterations(kEventMonitorSize - kRecuperableEvents, false);

    // Then
    EXPECT_FALSE(IsTriggerConditionMet());
    EXPECT_TRUE(IsResetConditionMet());
}

TEST_F(EventMonitorFixture, EventMonitor_GivenSequenceOfEvents_ExpectTriggerConditionMet)
{
    // Given
    const auto events_list = {true, true, false, true, false, true, true, true, true, true, true};

    // When
    RunFor(events_list);

    // Then
    EXPECT_TRUE(IsTriggerConditionMet());
}

}  // namespace
}  // namespace perception