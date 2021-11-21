///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
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
/// @param lhs [in] LVALUE
/// @param rhs [in] RVALUE
///
/// @return True if lhs == rhs, otherwise False
///
template <typename T>
constexpr bool operator==(const ValidityRange<T>& lhs, const ValidityRange<T>& rhs) noexcept
{
    return ((lhs.lower == rhs.lower) && (lhs.upper == rhs.upper));
}

///
/// @brief Inequality operator
///
/// @tparam T validity range type
///
/// @param lhs [in] LVALUE
/// @param rhs [in] RVALUE
///
/// @return True if lhs != rhs, otherwise False
///
template <typename T>
constexpr bool operator!=(const ValidityRange<T>& lhs, const ValidityRange<T>& rhs) noexcept
{
    return !(lhs == rhs);
}

///
/// @brief Check given value to be in range (lower, upper)
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param lower [in] lower value (excluding)
/// @param upper [in] upper value (excluding)
///
/// @return True if value is in given range (lower, upper), otherwise False.
///
template <typename T>
constexpr bool InRange(const T value, const T lower, const T upper) noexcept
{
    return ((value > lower) && (value < upper));
}

///
/// @brief Check given value to be in range (lower, upper)
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param range [in] validity range
///
/// @return True if value is in given range (lower, upper), otherwise False.
///
template <typename T>
constexpr bool InRange(const T value, const ValidityRange<T>& range) noexcept
{
    return InRange(value, range.lower, range.upper);
}

///
/// @brief Check given value to be in range inclusive to boundaries [lower, upper]
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param lower [in] lower value (including)
/// @param upper [in] upper value (including)
///
/// @return True if value is in given range [lower, upper], otherwise False.
///
template <typename T>
constexpr bool InRangeInclusive(const T value, const T lower, const T upper) noexcept
{
    return ((value >= lower) && (value <= upper));
}

///
/// @brief Check given value to be in range inclusive to bounaries [lower, upper]
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param range [in] validity range
///
/// @return True if value is in given range [lower, upper], otherwise False.
///
template <typename T>
constexpr bool InRangeInclusive(const T value, const ValidityRange<T>& range) noexcept
{
    return InRangeInclusive(value, range.lower, range.upper);
}

///
/// @brief Provided clamped value within range (lower, upper)
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param lower [in] lower value (excluding)
/// @param upper [in] upper value (excluding)
///
/// @return value if in given range (lower, upper), else lower if <lower and upper if > upper.
///
template <typename T>
constexpr T Clamp(const T value, const T lower, const T upper) noexcept
{
    return ((value < lower) ? lower : ((value > upper) ? upper : value));
}

///
/// @brief Provided clamped value within range (lower, upper)
/// @tparam Value type
///
/// @param value [in] value to be checked
/// @param range [in] validity range
///
/// @return value if in given range (lower, upper), else lower if <lower and upper if > upper.
///
template <typename T>
constexpr T Clamp(const T value, const ValidityRange<T>& range) noexcept
{
    return Clamp(value, range.lower, range.upper);
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_VALIDITY_RANGE_UTILS_H
