///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_EVENT_MONITOR_H
#define PERCEPTION_COMMON_EVENT_MONITOR_H

#include "perception/common/circular_bitset.h"

#include <iostream>

namespace perception
{
/// @brief Event Monitor implementation. Useful for recording timeframe based event counting
/// @tparam max_size [in] - Max Buffer Size
template <std::int32_t max_size>
class EventMonitor
{
  public:
    inline constexpr EventMonitor() : EventMonitor(0, 0) {}

    inline constexpr explicit EventMonitor(const std::int32_t acceptable_events, const std::int32_t recuperable_events)
        : acceptable_events_{acceptable_events}, recuperable_events_{recuperable_events}, event_buffer_{}
    {
    }

    inline constexpr void SetAcceptableEvents(const std::int32_t acceptable_events)
    {
        acceptable_events_ = acceptable_events;
    }

    inline constexpr void SetRecuperableEvents(const std::int32_t recuperable_events)
    {
        recuperable_events_ = recuperable_events;
    }

    inline constexpr void RecordEvent(const bool is_event_occurred) { event_buffer_.push_back(is_event_occurred); }

    inline constexpr bool IsTriggerConditionMet() const
    {
        std::cout << "event_buffer: " << event_buffer_.count() << std::endl;
        return (event_buffer_.count() > acceptable_events_);
    }
    inline constexpr bool IsResetConditionMet() const { return (event_buffer_.count() <= recuperable_events_); }

  private:
    std::int32_t acceptable_events_;
    std::int32_t recuperable_events_;
    CircularBitset<max_size> event_buffer_;
};

}  // namespace perception

#endif  /// PERCEPTION_COMMON_EVENT_MONITOR_H