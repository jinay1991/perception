///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMON_VALIDITY_RANGE_UTILS_H
#define PERCEPTION_COMMON_VALIDITY_RANGE_UTILS_H

#include <limits>

namespace perception
{
///
/// @brief Validity Range
/// @tparam range type
///
template <typename T>
struct ValidityRange
{
    /// @brief Lower Range
    T lower{std::numeric_limits<T>::max()};

    /// @brief Upper Range
    T upper{std::numeric_limits<T>::min()};
};

///
/// @brief Equality operator
///
/// @tparam T validity range type
///
/// @param lhs[in] LVALUE
/// @param rhs[in] RVALUE
///
/// @return True if lhs == rhs, otherwise False
///
template <typename T>
inline bool operator==(const ValidityRange<T>& lhs, const ValidityRange<T>& rhs) noexcept
{
    return ((lhs.lower == rhs.lower) && (lhs.upper == rhs.upper));
}

///
/// @brief Inequality operator
///
/// @tparam T validity range type
///
/// @param lhs[in] LVALUE
/// @param rhs[in] RVALUE
///
/// @return True if lhs != rhs, otherwise False
///
template <typename T>
inline bool operator!=(const ValidityRange<T>& lhs, const ValidityRange<T>& rhs) noexcept
{
    return !(lhs == rhs);
}

///
/// @brief Check given value to be in range (lower, upper)
/// @tparam Value type
///
/// @param value[in] value to be checked
/// @param lower[in] lower value (excluding)
/// @param upper[in] upper value (excluding)
///
/// @return True if value is in given range (lower, upper), otherwise False.
///
template <typename T>
inline constexpr bool InRange(const T value, const T lower, const T upper)
{
    return ((value > lower) && (value < upper));
}

///
/// @brief Check given value to be in range (lower, upper)
/// @tparam Value type
///
/// @param value[in] value to be checked
/// @param range[in] validity range
///
/// @return True if value is in given range (lower, upper), otherwise False.
///
template <typename T>
inline constexpr bool InRange(const T value, const ValidityRange<T>& range)
{
    return InRange(value, range.lower, range.upper);
}

///
/// @brief Provided clamped value within range (lower, upper)
/// @tparam Value type
///
/// @param value[in] value to be checked
/// @param lower[in] lower value (excluding)
/// @param upper[in] upper value (excluding)
///
/// @return value if in given range (lower, upper), else lower if <lower and upper if > upper.
///
template <typename T>
inline constexpr T Clamp(const T value, const T lower, const T upper)
{
    return ((value < lower) ? lower : ((value > upper) ? upper : value));
}

///
/// @brief Provided clamped value within range (lower, upper)
/// @tparam Value type
///
/// @param value[in] value to be checked
/// @param range[in] validity range
///
/// @return value if in given range (lower, upper), else lower if <lower and upper if > upper.
///
template <typename T>
inline constexpr T Clamp(const T value, const ValidityRange<T>& range)
{
    return Clamp(value, range.lower, range.upper);
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_VALIDITY_RANGE_UTILS_H
