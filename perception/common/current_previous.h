///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMON_CURRENT_PREVIOUS_H
#define PERCEPTION_COMMON_CURRENT_PREVIOUS_H

namespace perception
{
/// @brief Current/Previous Datastructure
///
/// @tparam Type T - Type for Current/Previous elements
template <typename T>
class CurrentPrevious
{
  public:
    /// @brief Default constructor.
    ///
    /// @param current - Value for Current
    /// @param previous - Value for previous
    explicit CurrentPrevious(const T& current, const T& previous) : current_{current}, previous_{previous} {}

    /// @brief Set Current data
    ///
    /// @param current_data [in] - Current data
    inline constexpr void SetCurrent(const T& current) { current_ = current; }

    /// @brief Set Previous data
    ///
    /// @param previous [in] - Previous data
    inline constexpr void SetPrevious(const T& previous) { previous_ = previous; }

    /// @brief Provide current
    ///
    /// @return current data
    inline constexpr const T& GetCurrent() const { return current_; }

    /// @brief Provide previous
    ///
    /// @return previous data
    inline constexpr const T& GetPrevious() const { return previous_; }

    /// @brief Provide delta between current & previous
    ///
    /// @return delta
    inline constexpr T GetDelta() const { return (current_ - previous_); }

  private:
    /// @brief Current element of type T
    T current_;

    /// @brief Previous element of type T
    T previous_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_CURRENT_PREVIOUS_H