///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_COMMON_CURRENT_PREVIOUS_H
#define PERCEPTION_COMMON_CURRENT_PREVIOUS_H

namespace perception
{
/// @brief Current/Previous Datastructure
///
/// @tparam Type T - Type for Current/Previous elements
template <typename T>
class CurrentPrevious final
{
  public:
    /// @brief Default constructor.
    ///
    /// @param current - Value for Current
    /// @param previous - Value for previous
    constexpr explicit CurrentPrevious(const T& current, const T& previous) : current_{current}, previous_{previous} {}

    /// @brief Set Current data
    ///
    /// @param current_data [in] - Current data
    constexpr void SetCurrent(const T& current) noexcept { current_ = current; }

    /// @brief Set Previous data
    ///
    /// @param previous [in] - Previous data
    constexpr void SetPrevious(const T& previous) noexcept { previous_ = previous; }

    /// @brief Provide current
    ///
    /// @return current data
    constexpr const T& GetCurrent() const noexcept { return current_; }

    /// @brief Provide previous
    ///
    /// @return previous data
    constexpr const T& GetPrevious() const noexcept { return previous_; }

    /// @brief Provide delta between current & previous
    ///
    /// @return delta
    constexpr T GetDelta() const noexcept { return (current_ - previous_); }

  private:
    /// @brief Current element of type T
    T current_;

    /// @brief Previous element of type T
    T previous_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_CURRENT_PREVIOUS_H
