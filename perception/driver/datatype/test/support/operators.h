///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/datatype/driver.h"

#include <ostream>
#include <string>

namespace perception
{
namespace driver
{

inline std::string to_string(const EyeState& eye_state) noexcept
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

inline std::ostream& operator<<(std::ostream& stream, const EyeState& eye_state) noexcept
{
    const auto name = to_string(eye_state);
    stream << name;
    return stream;
}

inline std::string to_string(const FatigueState& fatigue_state) noexcept
{
    switch (fatigue_state)
    {
        case FatigueState::kAwake:
            return "kAwake";
        case FatigueState::kQuestionable:
            return "kQuestionable";
        case FatigueState::kDrowsy:
            return "kDrowsy";
        case FatigueState::kBeginningSleep:
            return "kBeginningSleep";
        case FatigueState::kSleep:
            return "kSleep";
        case FatigueState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown FatigueState!";
    }
    return "ERROR: Unknown FatigueState!";
}

inline std::ostream& operator<<(std::ostream& stream, const FatigueState& fatigue_state) noexcept
{
    const auto name = to_string(fatigue_state);
    stream << name;
    return stream;
}

inline std::string to_string(const DistractionState& distraction_state) noexcept
{
    switch (distraction_state)
    {
        case DistractionState::kDistracted:
            return "kDistracted";
        case DistractionState::kNotDistracted:
            return "kNotDistracted";
        case DistractionState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown DistractionState!";
    }
    return "ERROR: Unknown DistractionState!";
}

inline std::ostream& operator<<(std::ostream& stream, const DistractionState& distraction_state) noexcept
{
    const auto name = to_string(distraction_state);
    stream << name;
    return stream;
}

inline std::string to_string(const ActivityState& activity_state) noexcept
{
    switch (activity_state)
    {
        case ActivityState::kNotAvailable:
            return "kNotAvailable";
        case ActivityState::kCalling:
            return "kCalling";
        case ActivityState::kTexting:
            return "kTexting";
        case ActivityState::kHandsOnWheel:
            return "kHandsOnWheel";
        case ActivityState::kHandsOffWheel:
            return "kHandsOffWheel";
        case ActivityState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown ActivityState!";
    }
    return "ERROR: Unknown ActivityState!";
}

inline std::ostream& operator<<(std::ostream& stream, const ActivityState& activity_state) noexcept
{
    const auto name = to_string(activity_state);
    stream << name;
    return stream;
}

inline std::string to_string(const RiskAssessmentState& activity_state) noexcept
{
    switch (activity_state)
    {
        case RiskAssessmentState::kNone:
            return "kNone";
        case RiskAssessmentState::kModerate:
            return "kModerate";
        case RiskAssessmentState::kHigh:
            return "kHigh";
        case RiskAssessmentState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown RiskAssessmentState!";
    }
    return "ERROR: Unknown RiskAssessmentState!";
}

inline std::ostream& operator<<(std::ostream& stream, const RiskAssessmentState& activity_state) noexcept
{
    const auto name = to_string(activity_state);
    stream << name;
    return stream;
}

inline std::string to_string(const ResponsivenessState& responsiveness_state) noexcept
{
    switch (responsiveness_state)
    {
        case ResponsivenessState::kNotAvailable:
            return "kNotAvailable";
        case ResponsivenessState::kNonResponsive:
            return "kNonResponsive";
        case ResponsivenessState::kResponsive:
            return "kResponsive";
        case ResponsivenessState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown ResponsivenessState!";
    }
    return "ERROR: Unknown ResponsivenessState!";
}

inline std::ostream& operator<<(std::ostream& stream, const ResponsivenessState& responsiveness_state) noexcept
{
    const auto name = to_string(responsiveness_state);
    stream << name;
    return stream;
}
}  // namespace driver
}  // namespace perception
