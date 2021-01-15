///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_H
#define PERCEPTION_DATATYPES_DRIVER_H

#include <units.h>

#include <chrono>

namespace perception
{

using namespace units::literals;
using namespace std::chrono_literals;

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMinEyeBlinkRate{0.0};

/// @brief Maximum eye blink rate (hertz)
static constexpr units::frequency::hertz_t kMaxEyeBlinkRate{30.0};

/// @brief Maximum eye lid opening (mm)
static constexpr units::length::millimeter_t kMaxEyeLidOpening{10.0};

/// @brief Minimum eye lid opening (mm)
static constexpr units::length::millimeter_t kMinEyeLidOpening{1.0};

/// @brief Maximum possible yaw angle for human head in range (rad). Range between 0-80_deg
static constexpr units::angle::radian_t kMaxHeadPoseYaw{80_deg};

/// @brief Maximum possible pitch angle for human head in range (rad). Range between 0-30_deg
static constexpr units::angle::radian_t kMaxHeadPosePitch{30_deg};

/// @brief Maximum possible roll angle for human head in range (rad). Range between 0-60_deg
static constexpr units::angle::radian_t kMaxHeadPoseRoll{60_deg};

/// @brief Maximum duration till which eye state is being observed (ms)
static constexpr std::chrono::milliseconds kMaxEyeStateObservationDuration{5min};

/// @brief Max assumed cycle duration (ms)
static constexpr std::chrono::milliseconds kMaxCycleDuration{40ms};

/// @brief Maximum allowed longterm storage size (i.e. max samples to store)
static constexpr std::int32_t kMaxLongtermStorageSize{kMaxEyeStateObservationDuration / kMaxCycleDuration};

/// @brief Eye State
enum class EyeState : std::uint8_t
{
    kEyesOpen = 0U,
    kEyesClosed = 1U,
    kEyesUnknown = 2U,
    kInvalid = 3U
};

/// @brief Fatigue Level
enum class FatigueLevel : std::uint8_t
{
    kAwake = 0U,
    kQuestionable = 1U,
    kDrowsy = 2U,
    kBeginningSleep = 3U,
    kSleep = 4U,
    kInvalid = 5U
};

/// @brief Visual Attention State
enum class AttentionState : std::uint8_t
{
    kAttentive = 0U,
    kNotAttentive = 1U,
    kInvalid = 2U
};

/// @brief Driver Face Tracking Information
struct FaceTracking
{
    /// @brief Driver Face Visibility
    bool face_visibility{false};

    /// @brief Driver Eye visibility
    bool eye_visibility{false};

    /// @brief Driver Eye lid opening (mm)
    units::length::millimeter_t eye_lid_opening{0.0};

    /// @brief Driver Eye blink rate (hertz)
    units::frequency::hertz_t eye_blink_rate{0.0};
};

/// @brief Driver Gaze Tracking Information
struct GazeTracking
{
    /// @brief Driver Gaze Tracking Yaw (rad)
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Gaze Tracking Pitch (rad)
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Gaze Tracking Roll (rad)
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Head Tracking Information
struct HeadTracking
{
    /// @brief Driver Head Tracking Yaw (rad)
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Head Tracking Pitch (rad)
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Head Tracking Roll (rad)
    units::angle::radian_t roll{0.0};
};

/// @brief Fatigue Information
struct FatigueMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Driver Eye state
    EyeState eye_state{EyeState::kInvalid};

    /// @brief Driver Fatigue Level
    FatigueLevel level{FatigueLevel::kInvalid};

    /// @brief Driver Fatigue Confidence. Range between 0.0-100.0%
    double confidence{0.0};
};

/// @brief Visual Attention Information
struct VisualAttentionMessage
{
    /// @brief Time Point for captured data
    std::chrono::system_clock::time_point time_point{};

    /// @brief Attention
    AttentionState attention_state{AttentionState::kInvalid};
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

/// @brief Equality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return ((lhs.face_visibility == rhs.face_visibility) && (lhs.eye_visibility == rhs.eye_visibility) &&
            (lhs.eye_lid_opening == rhs.eye_lid_opening) && (lhs.eye_blink_rate == rhs.eye_blink_rate));
}

/// @brief Inequality operator for elementwise comparision for FaceTracking
///
/// @param lhs [in] - lvalue (FaceTracking)
/// @param rhs [in] - rvalue (FaceTracking)
///
/// @return True if (lhs != rhs), otherwise false.
inline bool operator!=(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Equality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (GazeTracking)
/// @param rhs [in] - rvalue (GazeTracking)
///
/// @return True if (lhs != rhs), otherwise false.
inline bool operator!=(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Inequality operator for elementwise comparision for GazeTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

/// @brief Inequality operator for elementwise comparision for HeadTracking
///
/// @param lhs [in] - lvalue (HeadTracking)
/// @param rhs [in] - rvalue (HeadTracking)
///
/// @return True if (lhs != rhs), otherwise false.
inline bool operator!=(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Inequality operator for elementwise comparision for FatigueMessage
///
/// @param lhs [in] - lvalue (FatigueMessage)
/// @param rhs [in] - rvalue (FatigueMessage)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const FatigueMessage& lhs, const FatigueMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.eye_state == rhs.eye_state) && (lhs.level == rhs.level) &&
            (lhs.confidence == rhs.confidence));
}

/// @brief Inequality operator for elementwise comparision for FatigueMessage
///
/// @param lhs [in] - lvalue (FatigueMessage)
/// @param rhs [in] - rvalue (FatigueMessage)
///
/// @return True if (lhs != rhs), otherwise false.
inline bool operator!=(const FatigueMessage& lhs, const FatigueMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Inequality operator for elementwise comparision for VisualAttentionMessage
///
/// @param lhs [in] - lvalue (VisualAttentionMessage)
/// @param rhs [in] - rvalue (VisualAttentionMessage)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const VisualAttentionMessage& lhs, const VisualAttentionMessage& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.attention_state == rhs.attention_state));
}

/// @brief Inequality operator for elementwise comparision for VisualAttentionMessage
///
/// @param lhs [in] - lvalue (VisualAttentionMessage)
/// @param rhs [in] - rvalue (VisualAttentionMessage)
///
/// @return True if (lhs != rhs), otherwise false.
inline bool operator!=(const VisualAttentionMessage& lhs, const VisualAttentionMessage& rhs) noexcept
{
    return !(lhs == rhs);
}

/// @brief Inequality operator for elementwise comparision for DriverCameraMessage
///
/// @param lhs [in] - lvalue (DriverCameraMessage)
/// @param rhs [in] - rvalue (DriverCameraMessage)
///
/// @return True if (lhs == rhs), otherwise false.
inline bool operator==(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
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
inline bool operator!=(const DriverCameraMessage& lhs, const DriverCameraMessage& rhs) noexcept
{
    return !(lhs == rhs);
}
}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_DRIVER_H
