///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_COMMON_FILTER_H
#define PERCEPTION_COMMON_FILTER_H

#include <chrono>

namespace perception
{
using namespace std::chrono_literals;

/// @brief Filter - Removes false spikes in received signal by neglecting state change for certain duration before
/// accepting new state.
///
/// @tparam filter state type
template <typename T>
class Filter
{
  public:
    /// @brief Default Constructor
    ///
    /// @param initial_state [in] - Initial state or Invalid State
    explicit Filter(const T& initial_state)
        : initial_state_{initial_state},
          current_state_{initial_state_},
          previous_state_{initial_state_},
          hold_duration_{0ms},
          state_duration_{0ms},
          state_hold_duration_{0ms}
    {
    }
    /// @brief Update required state hold duration with provided duration
    ///
    /// @param duration [in] - New state hold duration (ms)
    inline constexpr void SetHoldDuration(const std::chrono::milliseconds duration) { hold_duration_ = duration; }

    /// @brief Provide current filtered state
    ///
    /// @return current state (template type T)
    inline constexpr const T& GetCurrentState() const { return current_state_; }

    /// @brief Provide current filtered state duration (ms)
    ///
    /// @return state duration (ms)
    inline constexpr std::chrono::milliseconds GetStateDuration() const { return state_duration_; }

    /// @brief Update current state. Changes to provided state only if state hold duration exceeds configured hold
    /// duration. This filters out spikes in signal which could lead to errorinous switch back-n-forth.
    ///
    /// @param new_state [in] - New state to be updated to
    /// @param delta_duration [in] - delta duration for which new_state was observed since last update.
    inline constexpr void Update(const T& new_state, const std::chrono::milliseconds delta_duration)
    {
        state_duration_ += delta_duration;

        if (IsCurrentStateValid() && IsStateValid(new_state))
        {
            if (IsStateChangeRequired(new_state))
            {
                state_hold_duration_ += delta_duration;

                if (IsStateChangePossible())
                {
                    ChangeState(new_state);
                }
                else
                {
                    // do nothing
                }
            }
            else
            {
                // Don't count up if there is no state change.
                state_hold_duration_ = 0ms;
            }
        }
        else
        {
            // Change state immediately in case of current_state is initial state
            ChangeState(new_state);
        }
    }

  private:
    /// @brief Check if provided state is valid (compares with initial state)
    ///
    /// @return True if state is not inital state, otherwise False
    inline constexpr bool IsStateValid(const T& state) const { return (state != initial_state_); }

    /// @brief Check if current state is valid (compares with initial state)
    ///
    /// @return True if state is not inital state, otherwise False
    inline constexpr bool IsCurrentStateValid() const { return IsStateValid(current_state_); }

    /// @brief Check if state change required for provided state (compares with current state)
    ///
    /// @return True if state is not same as current state, otherwise False
    inline constexpr bool IsStateChangeRequired(const T new_state) const { return (current_state_ != new_state); }

    /// @brief Check if current state hold duration exceeds required state hold duration.
    ///
    /// @return True if state hold duration exceeds required hold duration, otherwise False
    inline constexpr bool IsStateChangePossible() const { return (state_hold_duration_ > hold_duration_); }

    /// @brief Changes state to new state & resets state & state hold durations counters
    ///
    /// @param new_state [in] - New State for change
    inline constexpr void ChangeState(const T& new_state)
    {
        previous_state_ = current_state_;
        current_state_ = new_state;

        // Reset state attributes upon new state
        state_duration_ = 0ms;
        state_hold_duration_ = 0ms;
    }

    /// @brief Initial State (or Invalid State)
    const T initial_state_;

    /// @brief Current State
    T current_state_;

    /// @brief Previous State
    T previous_state_;

    /// @brief Required state hold duration (ms)
    std::chrono::milliseconds hold_duration_;

    /// @brief Current State duration (ms)
    std::chrono::milliseconds state_duration_;

    /// @brief Current State hold duration (ms)
    std::chrono::milliseconds state_hold_duration_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_FILTER_H
