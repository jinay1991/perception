///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMON_FILTER_H
#define PERCEPTION_COMMON_FILTER_H

#include "perception/common/logging.h"

#include <chrono>

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
          debounce_duration_{0ms},
          hold_duration_{0ms},
          state_duration_{0ms}
    {
    }

    ~Filter() = default;
    Filter(const Filter&) = delete;
    Filter& operator=(const Filter&) = delete;
    Filter(Filter&&) = delete;
    Filter& operator=(Filter&&) = delete;

    void SetHoldDuration(const std::chrono::milliseconds duration) { hold_duration_ = duration; }

    T GetCurrentState() const { return current_state_; }

    void Update(const T new_state, const std::chrono::milliseconds delta_duration)
    {
        if (current_state_ != new_state)
        {
            UpdateCurrentStateBasedOnHoldDuration(new_state, delta_duration);
        }
        else
        {
            // do nothing
        }
    }

  private:
    void UpdateCurrentStateBasedOnHoldDuration(const T new_state, const std::chrono::milliseconds delta_duration)
    {
        state_duration_ += delta_duration;
        if (state_duration_ > hold_duration_)
        {
            ChangeState(new_state);
        }
        else
        {
            // do nothing
        }
    }

    void ChangeState(const T new_state)
    {
        previous_state_ = current_state_;
        current_state_ = new_state;

        state_duration_ = 0ms;
    }

 
    const T initial_state_;
    T current_state_;
    T previous_state_;

    std::chrono::milliseconds debounce_duration_;
    std::chrono::milliseconds hold_duration_;
    std::chrono::milliseconds state_duration_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_FILTER_H
