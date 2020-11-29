///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/datatypes/driver.h"

#include <ostream>
#include <string>

namespace perception
{

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
