///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/datatypes/driver.h"

#include <ostream>
#include <string>

namespace perception
{

inline const char* to_string(const AttentionState& attention_state)
{
    switch (attention_state)
    {
        case AttentionState::kAttentive:
            return "kAttentive";
        case AttentionState::kNotAttentive:
            return "kNotAttentive";
        case AttentionState::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown AttentionState!";
    }
    return "ERROR: Unknown AttentionState!";
}

inline std::ostream& operator<<(std::ostream& stream, const AttentionState& attention_state)
{
    const char* name = to_string(attention_state);
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

inline const char* to_string(const FatigueLevel& fatigue_level)
{
    switch (fatigue_level)
    {
        case FatigueLevel::kAwake:
            return "kAwake";
        case FatigueLevel::kDrowsy:
            return "kDrowsy";
        case FatigueLevel::kBeginningSleep:
            return "kBeginningSleep";
        case FatigueLevel::kSleep:
            return "kSleep";
        case FatigueLevel::kInvalid:
            return "kInvalid";
        default:
            return "ERROR: Unknown FatigueLevel!";
    }
    return "ERROR: Unknown FatigueLevel!";
}

inline std::ostream& operator<<(std::ostream& stream, const FatigueLevel& fatigue_level)
{
    const char* name = to_string(fatigue_level);
    stream << name;
    return stream;
}
}  // namespace perception
