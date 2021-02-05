///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_EVENT_MONITOR_H
#define PERCEPTION_COMMON_EVENT_MONITOR_H

#include "perception/common/circular_bitset.h"

namespace perception
{
/// @brief Event Monitor implementation. Useful for recording timeframe based event counting
///
/// @tparam max_size [in] - Max Buffer Size
template <std::int32_t max_size>
class EventMonitor
{
  public:
    /// @brief Default Constructor
    inline constexpr EventMonitor() : EventMonitor(0, 0) {}

    /// @brief Constructor.
    ///
    /// @param acceptable_events [in] - Acceptable Events
    /// @param recuperable_events [in] - Recuperable Events
    inline constexpr explicit EventMonitor(const std::int32_t acceptable_events, const std::int32_t recuperable_events)
        : acceptable_events_{acceptable_events}, recuperable_events_{recuperable_events}, event_buffer_{}
    {
    }

    /// @brief Set acceptable number of events. Acceptable Events will be used to check when to trigger event request.
    /// @note Number of recorded events exceeds acceptable number of events will request event trigger.
    ///
    /// @param acceptable_events [in] - Acceptable Number of Events
    inline constexpr void SetAcceptableEvents(const std::int32_t acceptable_events)
    {
        acceptable_events_ = acceptable_events;
    }

    /// @brief Set recuperable number of events. Recuperable Events will be used to check when to reset the trigger.
    /// @note Number of recorded event falls below recuperable number of events will request reset of the triggered
    /// event.
    ///
    /// @param recuperable_events [in] - Recuperable Number of Events
    inline constexpr void SetRecuperableEvents(const std::int32_t recuperable_events)
    {
        recuperable_events_ = recuperable_events;
    }

    /// @brief Recording the Event to event monitor.
    ///
    /// @param is_event_occurred [in] - Event Status
    inline constexpr void RecordEvent(const bool is_event_occurred) { UpdateEvent(is_event_occurred); }

    /// @brief Check whether recorded number of events exceeds acceptable events, which implies trigger conditions are
    /// met.
    ///
    /// @return True, if number of events recorded in the buffer exceeds that of set acceptable number of events.
    inline constexpr bool IsTriggerConditionMet() const { return (event_buffer_.count() > acceptable_events_); }

    /// @brief Check whether recorded number of events reduces below recuperable events, which implies trigger reset
    /// conditions are met.
    ///
    /// @return True, if number of events recorded in the buffer reduces that of set recuperable number of events.
    inline constexpr bool IsResetConditionMet() const { return (event_buffer_.count() <= recuperable_events_); }

  private:
    /// @brief Update Event Buffer with provided event status
    ///
    /// @param is_event_occurred [in] - Event Status
    inline constexpr void UpdateEvent(const bool is_event_occurred) { event_buffer_.push_back(is_event_occurred); }

    /// @brief Acceptable Number of Events
    std::int32_t acceptable_events_;

    /// @brief Recuperable Number of Events
    std::int32_t recuperable_events_;

    /// @brief Event buffer of size (max_size)
    /// @note Provided max_size will define the window size to hold events for.
    CircularBitset<max_size> event_buffer_;
};

}  // namespace perception

#endif  /// PERCEPTION_COMMON_EVENT_MONITOR_H
