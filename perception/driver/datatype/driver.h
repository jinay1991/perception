///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_H
#define PERCEPTION_DATATYPES_DRIVER_H

#include <units.h>

#include <chrono>

namespace perception
{
namespace driver
{

using namespace units::literals;
using namespace std::chrono_literals;

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMinEyeBlinkRate{0.15_Hz};

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMaxEyeBlinkRate{0.5_Hz};

/// @brief Maximum eye lid opening (mm)
static constexpr units::length::millimeter_t kMaxEyeLidOpening{10.0};

/// @brief Minimum eye lid opening (mm)
static constexpr units::length::millimeter_t kMinEyeLidOpening{1.0};

/// @brief Maximum possible yaw angle for human head in range (rad). Range between -80 to 75 deg
static constexpr units::angle::radian_t kMinHeadPoseYaw = units::angle::degree_t{-80.0};

/// @brief Maximum possible yaw angle for human head in range (rad). Range between -80 to 75 deg
static constexpr units::angle::radian_t kMaxHeadPoseYaw = units::angle::degree_t{75.0};

/// @brief Maximum possible pitch angle for human head in range (rad). Range between -60 to 70 deg
static constexpr units::angle::radian_t kMinHeadPosePitch = units::angle::degree_t{-60.0};

/// @brief Maximum possible pitch angle for human head in range (rad). Range between -60 to 70 deg
static constexpr units::angle::radian_t kMaxHeadPosePitch = units::angle::degree_t{70.0};

/// @brief Maximum possible roll angle for human head in range (rad). Range between -40 to 36 deg
static constexpr units::angle::radian_t kMinHeadPoseRoll = units::angle::degree_t{-40.0};

/// @brief Maximum possible roll angle for human head in range (rad). Range between -40 to 36 deg
static constexpr units::angle::radian_t kMaxHeadPoseRoll = units::angle::degree_t{36.0};

/// @brief Maximum duration till which eye state is being observed (ms)
static constexpr std::chrono::milliseconds kMaxEyeStateObservationDuration{5min};

/// @brief Max assumed cycle duration (ms)
static constexpr std::chrono::milliseconds kMaxCycleDuration{40ms};

/// @brief Maximum allowed longterm storage size (i.e. max samples to store)
static constexpr std::size_t kMaxLongtermStorageSize{kMaxEyeStateObservationDuration / kMaxCycleDuration};

/// @brief Minimum (ego) velocity required for active Driver Monitoring (NCAP Requirement)
static constexpr units::velocity::meters_per_second_t kMinVelocity{10_kph};

/// @brief Maximum (ego) velocity required for active Driver Monitoring (NCAP Requirement)
static constexpr units::velocity::meters_per_second_t kMaxVelocity{200_kph};

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

/// @brief Driver Face Tracking Information
struct FaceTracking
{
    /// @brief Driver Face Visibility
    bool face_visible{false};

    /// @brief Driver Eye visibility
    bool eye_visible{false};

    /// @brief Driver Eye lid opening (mm)
    units::length::millimeter_t eye_lid_opening{0.0};

    /// @brief Driver Eye blink rate (hertz)
    units::frequency::hertz_t eye_blink_rate{0.0};
};

/// @brief Driver Gaze Tracking Information
struct GazeTracking
{
    /// @brief Driver Gaze Tracking Yaw (rad) - Left/Right Movements
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Gaze Tracking Pitch (rad) - Up/Down Movements
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Gaze Tracking Roll (rad) - Diagonal Left/Right Movements
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Head Tracking Information
struct HeadTracking
{
    /// @brief Driver Head Tracking Yaw (rad) - Left/Right Movements
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Head Tracking Pitch (rad) - Up/Down Movements
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Head Tracking Roll (rad) - Diagonal/Tilt Left/Right Movements
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Camera System Information
struct DriverCameraMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Head Tracking Information
    HeadTracking head_tracking{};

    /// @brief Face Tracking Information
    FaceTracking face_tracking{};

    /// @brief Gaze Tracking Information
    GazeTracking gaze_tracking{};
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

/// @brief Equality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return ((lhs.face_visible == rhs.face_visible) && (lhs.eye_visible == rhs.eye_visible) &&
            (lhs.eye_lid_opening == rhs.eye_lid_opening) && (lhs.eye_blink_rate == rhs.eye_blink_rate));
}

/// @brief Inequality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for HeadTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

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
/// @brief Equality operator for elementwise comparision for DriverCameraMessage
///
/// @param lhs [in] - lvalue (DriverCameraMessage)
/// @param rhs [in] - rvalue (DriverCameraMessage)
///
/// @return True if (lhs == rhs), otherwise false.
constexpr bool operator==(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.head_tracking == rhs.head_tracking) &&
            (lhs.face_tracking == rhs.face_tracking) && (lhs.gaze_tracking == rhs.gaze_tracking));
}

/// @brief Inequality operator for elementwise comparision for DriverCameraMessage
///
/// @param lhs [in] - lvalue (DriverCameraMessage)
/// @param rhs [in] - rvalue (DriverCameraMessage)
///
/// @return True if (lhs != rhs), otherwise false.
constexpr bool operator!=(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
{
    return !(lhs == rhs);
}
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DATATYPES_DRIVER_H
