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

enum class EyeState
{
    kOpenEyes = 0,
    kCloseEyes = 1,
    kInvalid = 2
};

enum class HeadPose
{
    kAttentive = 0,
    kNotAttentive = 1,
    kInvalid = 2
};

enum class GazePose
{
    kFront = 0,
    kLeft = 1,
    kRight = 2,
    kDown = 3,
    kUp = 4,
    kInvalid = 5
};

enum class DegradationState
{
    kNormalOperation = 0,
    kValidityError = 1,
    kOutOfRange = 2,
    kCommunicationError = 3,
    kSensorBlockage = 4,
    kInvalid = 5
};

struct DegradationMessage
{
    DegradationState state;
};

struct FatigueMessage
{
    EyeState eye_state;
};

struct VisualAttentionMessage
{
    HeadPose head_pose;
    GazePose gaze_pose;
};

struct FaceTracking
{
    bool eye_visibility;
    units::length::millimeter_t eye_lid_opening;
    units::frequency::hertz_t eye_blink_rate;
};

struct GazeTracking
{
    units::angle::radian_t yaw;
    units::angle::radian_t pitch;
    units::angle::radian_t roll;
};

struct HeadTracking
{
    units::angle::radian_t yaw;
    units::angle::radian_t pitch;
    units::angle::radian_t roll;
};

struct DriverCameraSystem
{
    HeadTracking head_tracking;
    FaceTracking face_tracking;
    GazeTracking gaze_tracking;
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
    return ((lhs.head_tracking == rhs.head_tracking) && (lhs.face_tracking == rhs.face_tracking) &&
            (lhs.gaze_tracking == rhs.gaze_tracking));
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
        case DegradationState::kOutOfRange:
            return "kOutOfRange";
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
        case EyeState::kOpenEyes:
            return "kOpenEyes";
        case EyeState::kCloseEyes:
            return "kCloseEyes";
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
