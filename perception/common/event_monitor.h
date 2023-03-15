///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_COMMON_EVENT_MONITOR_H
#define PERCEPTION_COMMON_EVENT_MONITOR_H

#include "perception/common/circular_bitset.h"

#include <chrono>

namespace perception
{

using namespace std::chrono_literals;

/// @brief Event Monitor implementation. Useful for recording timeframe based event counting
///
/// @tparam kMaxNumberOfEvents [in] - Max Number of Events
template <std::int32_t kMaxNumberOfEvents>
class EventMonitor final
{
  public:
    /// @brief Default Constructor
    constexpr EventMonitor() : acceptable_events_{}, recuperable_events_{}, time_frame_{}, event_buffer_{} {}

    /// @brief Set time frame to observe
    ///
    /// @param time_frame [in] - Time frame to watch events.
    constexpr void SetTimeFrame(const std::chrono::milliseconds time_frame) noexcept { time_frame_ = time_frame; }

    /// @brief Set acceptable number of events. Acceptable Events will be used to check when to trigger event request.
    /// @note Number of recorded events exceeds acceptable number of events will request event trigger.
    ///
    /// @param acceptable_events [in] - Acceptable Number of Events
    constexpr void SetAcceptableEvents(const std::int32_t acceptable_events) noexcept
    {
        acceptable_events_ = acceptable_events;
    }

    /// @brief Set recuperable number of events. Recuperable Events will be used to check when to reset the trigger.
    /// @note Number of recorded event falls below recuperable number of events will request reset of the triggered
    /// event.
    ///
    /// @param recuperable_events [in] - Recuperable Number of Events
    constexpr void SetRecuperableEvents(const std::int32_t recuperable_events) noexcept
    {
        recuperable_events_ = recuperable_events;
    }

    /// @brief Recording the Event to event monitor.
    ///
    /// @param is_event_occurred [in] - Event Status
    /// @param delta_duration [in] - Delta time of events
    constexpr void RecordEvent(const bool is_event_occurred, const std::chrono::milliseconds delta_duration) noexcept
    {
        UpdateEventBuffer(is_event_occurred, delta_duration);
        DetermineCurrentNumberOfEvents();
        DetermineNumberOfEventsAboveThreshold();
    }

    /// @brief Provide Current Number of Events
    ///
    /// @return current_number_of_events in given time_frame
    constexpr std::int32_t GetCurrentNumberOfEvents() const noexcept { return current_number_of_events_; }

    /// @brief Check whether recorded number of events exceeds acceptable events, which implies trigger conditions are
    /// met.
    ///
    /// @return True, if number of events recorded in the buffer exceeds that of set acceptable number of events.
    constexpr bool IsNumberOfEventsAboveThreshold() const noexcept
    {
        return (GetCurrentNumberOfEvents() > acceptable_events_);
    }

    /// @brief Performs reset to Event Monitor. Reset all the internal state attributes
    constexpr void Reset() noexcept
    {
        acceptable_events_ = 0;
        recuperable_events_ = 0;
        current_number_of_events_ = 0;
        is_number_of_events_above_threshold_ = false;

        time_frame_ = 0ms;
        time_since_last_event_ = 0ms;

        event_buffer_.clear();
    }

  private:
    /// @brief Update Event Buffer with provided event status
    ///
    /// @param is_event_occurred [in] - Event Status
    /// @param delta_duration [in] - Delta duration between calls (usually cycle duration)
    constexpr void UpdateEventBuffer(const bool is_event_occurred,
                                     const std::chrono::milliseconds delta_duration) noexcept
    {

        time_since_last_event_ += delta_duration;
        if (is_event_occurred)
        {
            for (auto i = 0ms; i < delta_duration; i += 10ms)
            {
                event_buffer_.push_back(is_event_occurred);
            }
            time_since_last_event_ = 0ms;
        }
    }

    /// @brief Determine Current Number Of Events from event buffer
    constexpr void DetermineCurrentNumberOfEvents() noexcept
    {
        current_number_of_events_ = 0;
        std::chrono::milliseconds accumulated_duration = time_since_last_event_;

        for (auto i = event_buffer_.size(); i >= 0; --i)
        {
            if (time_frame_ <= accumulated_duration)
            {
                break;
            }

            accumulated_duration += 10ms;
            current_number_of_events_++;
        }
    }

    /// @brief Determine if current number of events exceeds acceptable events or falls below recuperable events.
    constexpr void DetermineNumberOfEventsAboveThreshold() noexcept
    {
        if (GetCurrentNumberOfEvents() > acceptable_events_)
        {
            is_number_of_events_above_threshold_ = true;
        }
        else if (GetCurrentNumberOfEvents() <= recuperable_events_)
        {
            is_number_of_events_above_threshold_ = false;
        }
        else
        {
            // do nothing
        }
    }

    /// @brief Acceptable Number of Events
    std::int32_t acceptable_events_;

    /// @brief Recuperable Number of Events
    std::int32_t recuperable_events_;

    /// @brief record current Number of Events
    std::int32_t current_number_of_events_;

    /// @brief Status of Number Of Events based on acceptable events and recuperable events.
    bool is_number_of_events_above_threshold_;

    /// @brief Time frame to observe events
    std::chrono::milliseconds time_frame_;

    /// @brief Time since last event has recorded
    std::chrono::milliseconds time_since_last_event_;

    /// @brief Event buffer of size (kMaxNumberOfEvents)
    /// @note Provided kMaxNumberOfEvents will define the window size to hold events for.
    /// @see CircularBitset
    CircularBitset<kMaxNumberOfEvents> event_buffer_;
};

}  // namespace perception

#endif  /// PERCEPTION_COMMON_EVENT_MONITOR_H
