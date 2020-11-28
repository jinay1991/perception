///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DATATYPES_DRIVER_H
#define PERCEPTION_DATATYPES_DRIVER_H

#include <units.h>

#include <ostream>
#include <string>

namespace perception
{

/// @brief Eye State
enum class EyeState : std::uint8_t
{
    kEyesOpen = 0U,
    kEyesClosed = 1U,
    kEyesUnknown = 2U,
    kInvalid = 3U
};

/// @brief Head Pose
enum class HeadPose : std::uint8_t
{
    kAttentive = 0U,
    kNotAttentive = 1U,
    kInvalid = 2U
};

/// @brief Gaze Pose
enum class GazePose : std::uint8_t
{
    kFront = 0U,
    kLeft = 1U,
    kRight = 2U,
    kDown = 3U,
    kUp = 4U,
    kInvalid = 5U
};

/// @brief Degradation State
enum class DegradationState : std::uint8_t
{
    kNormalOperation = 0U,
    kValidityError = 1U,
    kCommunicationError = 2U,
    kSensorBlockage = 3U,
    kInvalid = 4U
};

/// @brief Degradation Information
struct DegradationMessage
{
    /// @brief Degradation State
    DegradationState state{DegradationState::kInvalid};
};

/// @brief Fatigue Information
struct FatigueMessage
{
    /// @brief Driver Eye state
    EyeState eye_state{EyeState::kInvalid};
};

/// @brief Visual Attention Information
struct VisualAttentionMessage
{
    /// @brief Driver Head Pose
    HeadPose head_pose{HeadPose::kInvalid};

    /// @brief Driver Gaze Pose
    GazePose gaze_pose{GazePose::kInvalid};
};

/// @brief Driver Face Tracking Information
struct FaceTracking
{
    /// @brief Driver Eye visibility
    bool eye_visibility{false};

    /// @brief Driver Eye lid opening
    units::length::millimeter_t eye_lid_opening{0.0};

    /// @brief Driver Eye blink rate
    units::frequency::hertz_t eye_blink_rate{0.0};
};

/// @brief Driver Gaze Tracking Information
struct GazeTracking
{
    /// @brief Driver Gaze Tracking Yaw
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Gaze Tracking Pitch
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Gaze Tracking Roll
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Head Tracking Information
struct HeadTracking
{
    /// @brief Driver Head Tracking Yaw
    units::angle::radian_t yaw{0.0};

    /// @brief Driver Head Tracking Pitch
    units::angle::radian_t pitch{0.0};

    /// @brief Driver Head Tracking Roll
    units::angle::radian_t roll{0.0};
};

/// @brief Driver Camera System Information
struct DriverCameraSystem
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

inline bool operator==(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return ((lhs.eye_visibility == rhs.eye_visibility) && (lhs.eye_lid_opening == rhs.eye_lid_opening) &&
            (lhs.eye_blink_rate == rhs.eye_blink_rate));
}

inline bool operator!=(const FaceTracking& lhs, const FaceTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator==(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

inline bool operator!=(const GazeTracking& lhs, const GazeTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator==(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

inline bool operator!=(const HeadTracking& lhs, const HeadTracking& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator==(const DriverCameraSystem& lhs, const DriverCameraSystem& rhs) noexcept
{
    return ((lhs.time_point == rhs.time_point) && (lhs.head_tracking == rhs.head_tracking) &&
            (lhs.face_tracking == rhs.face_tracking) && (lhs.gaze_tracking == rhs.gaze_tracking));
}

inline bool operator!=(const DriverCameraSystem& lhs, const DriverCameraSystem& rhs) noexcept
{
    return !(lhs == rhs);
}

inline const char* to_string(const DegradationState& degradation_state)
{
    switch (degradation_state)
    {
        case DegradationState::kNormalOperation:
            return "kNormalOperation";
        case DegradationState::kValidityError:
            return "kValidityError";
        case DegradationState::kCommunicationError:
            return "kCommunicationError";
        case DegradationState::kSensorBlockage:
            return "kSensorBlockage";
        case DegradationState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown DegradationState!";
    }
    return "ERROR: Unknown DegradationState!";
}

inline std::ostream& operator<<(std::ostream& stream, const DegradationState& degradation_state)
{
    const char* name = to_string(degradation_state);
    stream << name;
    return stream;
}

inline const char* to_string(const HeadPose& head_pose)
{
    switch (head_pose)
    {
        case HeadPose::kAttentive:
            return "kAttentive";
        case HeadPose::kNotAttentive:
            return "kNotAttentive";
        case HeadPose::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown HeadPose!";
    }
    return "ERROR: Unknown HeadPose!";
}

inline std::ostream& operator<<(std::ostream& stream, const HeadPose& head_pose)
{
    const char* name = to_string(head_pose);
    stream << name;
    return stream;
}

inline const char* to_string(const GazePose& gaze_pose)
{
    switch (gaze_pose)
    {
        case GazePose::kFront:
            return "kFront";
        case GazePose::kLeft:
            return "kLeft";
        case GazePose::kRight:
            return "kRight";
        case GazePose::kDown:
            return "kDown";
        case GazePose::kUp:
            return "kUp";
        case GazePose::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown GazePose!";
    }
    return "ERROR: Unknown GazePose!";
}

inline std::ostream& operator<<(std::ostream& stream, const GazePose& gaze_pose)
{
    const char* name = to_string(gaze_pose);
    stream << name;
    return stream;
}

inline const char* to_string(const EyeState& eye_state)
{
    switch (eye_state)
    {
        case EyeState::kEyesOpen:
            return "kEyesOpen";
        case EyeState::kEyesClosed:
            return "kEyesClosed";
        case EyeState::kEyesUnknown:
            return "kEyesUnknown";
        case EyeState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown EyeState!";
    }
    return "ERROR: Unknown EyeState!";
}

inline std::ostream& operator<<(std::ostream& stream, const EyeState& eye_state)
{
    const char* name = to_string(eye_state);
    stream << name;
    return stream;
}

}  // namespace perception

#endif  /// PERCEPTION_DATATYPES_DRIVER_H
