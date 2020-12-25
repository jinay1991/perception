///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMON_FILTER_H
#define PERCEPTION_COMMON_FILTER_H

#include <chrono>
#include <iostream>
namespace perception
{
using namespace std::chrono_literals;

template <typename T>
class Filter
{
  public:
    explicit Filter(const T initial_state)
        : initial_state_{initial_state},
          current_state_{initial_state_},
          previous_state_{initial_state_},
          hold_duration_{0ms},
          state_duration_{0ms}
    {
    }

    inline void SetHoldDuration(const std::chrono::milliseconds duration) { hold_duration_ = duration; }

    inline constexpr T GetCurrentState() const { return current_state_; }
    inline constexpr std::chrono::milliseconds GetStateDuration() const { return state_duration_; }

    void Update(const T new_state, const std::chrono::milliseconds delta_duration)
    {
        if (IsCurrentStateValid() && IsStateValid(new_state))
        {
            state_duration_ += delta_duration;

            if (IsStateChangeRequired(new_state) && IsStateChangePossible())
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
            ChangeState(new_state);
        }
    }

  private:
    inline constexpr bool IsStateValid(const T state) const { return (state != initial_state_); }
    inline constexpr bool IsCurrentStateValid() const { return IsStateValid(current_state_); }
    inline constexpr bool IsStateChangeRequired(const T new_state) const { return (current_state_ != new_state); }
    inline constexpr bool IsStateChangePossible() const { return (state_duration_ > hold_duration_); }

    inline void ChangeState(const T new_state)
    {
        previous_state_ = current_state_;
        current_state_ = new_state;

        state_duration_ = 0ms;
    }

    const T initial_state_;
    T current_state_;
    T previous_state_;

    std::chrono::milliseconds hold_duration_;
    std::chrono::milliseconds state_duration_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_FILTER_H
