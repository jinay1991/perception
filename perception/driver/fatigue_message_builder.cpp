///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue_message_builder.h"

namespace perception
{
FatigueMessageBuilder::FatigueMessageBuilder() : fatigue_message_{} {}

FatigueMessageBuilder& FatigueMessageBuilder::WithTimepoint(const std::chrono::system_clock::time_point& time_point)
{
    fatigue_message_.time_point = time_point;
    return *this;
}

FatigueMessageBuilder& FatigueMessageBuilder::WithFatigueLevel(const FatigueLevel level)
{
    fatigue_message_.level = level;
    return *this;
}

FatigueMessageBuilder& FatigueMessageBuilder::WithFatigueConfidence(const double confidence)
{
    fatigue_message_.confidence = confidence;
    return *this;
}

FatigueMessageBuilder& FatigueMessageBuilder::WithEyeState(const EyeState eye_state)
{
    fatigue_message_.eye_state = eye_state;
    return *this;
}

const FatigueMessage& FatigueMessageBuilder::Build() const
{
    return fatigue_message_;
}
}  // namespace perception
