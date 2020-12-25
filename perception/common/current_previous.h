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

    /// @brief Provide delta between current - previous
    ///
    /// @return delta
    T GetDelta() const { return (current_ - previous_); }

  private:
    /// @brief Current element of type T
    const T current_;

    /// @brief Previous element of type T
    const T previous_;
};
}  // namespace perception

#endif  /// PERCEPTION_COMMON_CURRENT_PREVIOUS_H