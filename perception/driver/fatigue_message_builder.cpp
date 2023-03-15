///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/fatigue_message_builder.h"

namespace perception
{
namespace driver
{
FatigueMessageBuilder::FatigueMessageBuilder() : fatigue_message_{} {}

FatigueMessageBuilder& FatigueMessageBuilder::WithTimePoint(const std::chrono::system_clock::time_point& time_point)
{
    fatigue_message_.time_point = time_point;
    return *this;
}

FatigueMessageBuilder& FatigueMessageBuilder::WithState(const FatigueState state)
{
    fatigue_message_.state = state;
    return *this;
}

FatigueMessageBuilder& FatigueMessageBuilder::WithConfidence(const double confidence)
{
    fatigue_message_.confidence = confidence;
    return *this;
}

const FatigueMessage& FatigueMessageBuilder::Build() const
{
    return fatigue_message_;
}
}  // namespace driver
}  // namespace perception
