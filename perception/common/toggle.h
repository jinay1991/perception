///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_COMMON_TOGGLE_H
#define PERCEPTION_COMMON_TOGGLE_H

#include <chrono>

namespace perception
{
using namespace std::chrono_literals;

/// @brief Toggle State
///
/// @tparam State [in] - State Type
template <typename State, std::enable_if_t<std::is_enum<State>::value, bool> = true>
class Toggle final
{
  public:
    /// @brief Default Constructor
    /// @note Toggles between ON <-> OFF, where initial state is set to OFF.
    ///
    /// @param state_on [in] - State ON
    /// @param state_off [in] - State OFF
    constexpr explicit Toggle(const State state_on, const State state_off)
        : state_on_{state_on}, state_off_{state_off}, current_state_{false}, toggle_duration_{0ms}, state_duration_{0ms}
    {
    }

    /// @brief Update toggle duration (duration between each toggle ON <-> OFF)
    ///
    /// @param toggle_duration [in] - Toggle Duration (ms)
    constexpr void SetToggleDuration(const std::chrono::milliseconds toggle_duration) noexcept
    {
        toggle_duration_ = toggle_duration;
    }

    /// @brief Check and toggle state based on the toggle duration
    ///
    /// @param delta_duration [in] - Delta time duration between each update
    constexpr void Update(const std::chrono::milliseconds delta_duration) noexcept
    {
        state_duration_ += delta_duration;
        if (IsToggleStatePossible())
        {
            ToggleState();
        }
    }

    /// @brief Provide current state (i.e. ON or OFF)
    ///
    /// @return current state
    constexpr State GetCurrentState() const noexcept { return (current_state_ ? state_on_ : state_off_); }

  private:
    /// @brief Check if state toggle is possible
    ///
    /// @return True if current state duration exceeds toggle duration
    constexpr bool IsToggleStatePossible() const noexcept { return (state_duration_ > toggle_duration_); }

    /// @brief Update current state by toggling it's state and reseting current state duration
    constexpr void ToggleState() noexcept
    {
        current_state_ = (!current_state_);
        state_duration_ = 0ms;
    }

    /// @brief State ON
    const State state_on_;

    /// @brief State OFF
    const State state_off_;

    /// @brief Current State
    /// @note True implies State ON. False implies State OFF
    bool current_state_;

    /// @brief Set toggle duration
    std::chrono::milliseconds toggle_duration_;

    /// @brief Current state duration
    std::chrono::milliseconds state_duration_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_TOGGLE_H
