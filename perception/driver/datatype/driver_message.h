///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_MESSAGE_H
#define PERCEPTION_DATATYPES_DRIVER_MESSAGE_H

#include <units.h>

#include <chrono>
#include <cmath>

namespace perception
{
namespace driver
{

/// @brief Eye State
enum class EyeState : std::uint8_t
{
    kEyesOpen = 0U,
    kEyesClosed = 1U,
    kEyesUnknown = 2U,
    kInvalid = 255U
};

/// @brief Fatigue state (mapped to Karolinska Sleepiness Scale - KSS)
enum class FatigueState : std::uint8_t
{
    kAwake = 0U,           // KSS 1-5 (Alert)
    kQuestionable = 1U,    // KSS 5   (Neither drowsy nor alert)
    kDrowsy = 2U,          // KSS 6-7 (Drowsy)
    kBeginningSleep = 3U,  // KSS 8   (Sleepy)
    kSleep = 4U,           // KSS 9   (Extremely sleepy, fighting sleep)
    kInvalid = 255U
};

/// @brief Distraction State
enum class DistractionState : std::uint8_t
{
    kDistracted = 0U,
    kNotDistracted = 1U,
    kInvalid = 255U
};

/// @brief Activity State
enum class ActivityState : std::uint8_t
{
    kNotAvailable = 0U,
    kCalling = 1U,
    kTexting = 2U,
    kHandsOnWheel = 3U,
    kHandsOffWheel = 4U,
    kInvalid = 255U
};

/// @brief Risk Assessment State
enum class RiskAssessmentState : std::uint8_t
{
    kNone = 0U,
    kModerate = 1U,
    kHigh = 2U,
    kInvalid = 255U
};

/// @brief Responsiveness State
enum class ResponsivenessState : std::uint8_t
{
    kNotAvailable = 0U,
    kNonResponsive = 1U,
    kResponsive = 2U,
    kInvalid = 255U
};

/// @brief Driver Fatigue Information
struct FatigueMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver Fatigue state
    FatigueState state{FatigueState::kInvalid};

    /// @brief Driver Fatigue Confidence. Range between 0.0-100.0%
    double confidence{0.0};
};

/// @brief Driver Distraction Information
struct DistractionMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver's Distraction State
    DistractionState state{DistractionState::kInvalid};

    /// @brief Driver's Distraction State confidence. Range between 0.0-100.0%
    double confidence{0.0};
};

/// @brief Driver Activity Information
struct ActivityMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver's activity state
    ActivityState state{ActivityState::kInvalid};

    /// @brief Driver's activity State confidence. Range between 0.0-100.0%
    double confidence{0.0};
};

/// @brief Driver's Responsiveness Information
struct ResponsivenessMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver's responsiveness state
    ResponsivenessState state{ResponsivenessState::kInvalid};

    /// @brief Driver's responsiveness state confidence. Range between 0.0-100.0%
    double confidence{0.0};
};

/// @brief Driver's State Message
struct DriverMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver's Fatigue
    FatigueMessage fatigue{};

    /// @brief Driver's Distraction
    DistractionMessage distraction{};

    /// @brief Driver's Activity
    ActivityMessage activity{};

    /// @brief Driver's Responsiveness
    ResponsivenessMessage responsiveness{};
};

/// @brief Equality operator for elementwise comparision for FatigueMessage
///
/// @param lhs [in] - lvalue (FatigueMessage)
/// @param rhs [in] - rvalue (FatigueMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const FatigueMessage& lhs, const FatigueMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.state == rhs.state) &&
            (std::fabs(lhs.confidence - rhs.confidence) < std::numeric_limits<decltype(lhs.confidence)>::epsilon()));
}

/// @brief Inequality operator for elementwise comparision for FatigueMessage
///
/// @param lhs [in] - lvalue (FatigueMessage)
/// @param rhs [in] - rvalue (FatigueMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const FatigueMessage& lhs, const FatigueMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for DistractionMessage
///
/// @param lhs [in] - lvalue (DistractionMessage)
/// @param rhs [in] - rvalue (DistractionMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const DistractionMessage& lhs, const DistractionMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.state == rhs.state) &&
            (std::fabs(lhs.confidence - rhs.confidence) < std::numeric_limits<decltype(lhs.confidence)>::epsilon()));
}

/// @brief Inequality operator for elementwise comparision for DistractionMessage
///
/// @param lhs [in] - lvalue (DistractionMessage)
/// @param rhs [in] - rvalue (DistractionMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const DistractionMessage& lhs, const DistractionMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for ActivityMessage
///
/// @param lhs [in] - lvalue (ActivityMessage)
/// @param rhs [in] - rvalue (ActivityMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const ActivityMessage& lhs, const ActivityMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.state == rhs.state) &&
            (std::fabs(lhs.confidence - rhs.confidence) < std::numeric_limits<decltype(lhs.confidence)>::epsilon()));
}

/// @brief Inequality operator for elementwise comparision for ActivityMessage
///
/// @param lhs [in] - lvalue (ActivityMessage)
/// @param rhs [in] - rvalue (ActivityMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const ActivityMessage& lhs, const ActivityMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for ResponsivenessMessage
///
/// @param lhs [in] - lvalue (ResponsivenessMessage)
/// @param rhs [in] - rvalue (ResponsivenessMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const ResponsivenessMessage& lhs, const ResponsivenessMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.state == rhs.state) &&
            (std::fabs(lhs.confidence - rhs.confidence) < std::numeric_limits<decltype(lhs.confidence)>::epsilon()));
}

/// @brief Inequality operator for elementwise comparision for ResponsivenessMessage
///
/// @param lhs [in] - lvalue (ResponsivenessMessage)
/// @param rhs [in] - rvalue (ResponsivenessMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const ResponsivenessMessage& lhs, const ResponsivenessMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for DriverMessage
///
/// @param lhs [in] - lvalue (DriverMessage)
/// @param rhs [in] - rvalue (DriverMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const DriverMessage& lhs, const DriverMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.fatigue == rhs.fatigue) &&
            (lhs.distraction == rhs.distraction) && (lhs.activity == rhs.activity) &&
            (lhs.responsiveness == rhs.responsiveness));
}

/// @brief Inequality operator for elementwise comparision for DriverMessage
///
/// @param lhs [in] - lvalue (DriverMessage)
/// @param rhs [in] - rvalue (DriverMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const DriverMessage& lhs, const DriverMessage& rhs) noexcept
{
    return !(lhs == rhs);
}
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DATATYPES_DRIVER_MESSAGE_H
